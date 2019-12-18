#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct ipw_scan_request_ext {int* channels_list; int /*<<< orphan*/  full_scan_index; void** dwell_time; } ;
struct ipw_priv {int status; scalar_t__ direct_scan_ssid_len; int config; int channel; scalar_t__ essid_len; int /*<<< orphan*/  mutex; int /*<<< orphan*/  scan_check; int /*<<< orphan*/  essid; int /*<<< orphan*/  direct_scan_ssid; TYPE_1__* ieee; } ;
typedef  int /*<<< orphan*/  scan ;
struct TYPE_3__ {scalar_t__ iw_mode; } ;

/* Variables and functions */
 int CFG_SPEED_SCAN ; 
 int CFG_STATIC_ESSID ; 
 int IPW_A_MODE ; 
 int IPW_B_MODE ; 
 int /*<<< orphan*/  IPW_DEBUG_HC (char*,...) ; 
 int /*<<< orphan*/  IPW_DEBUG_WX (char*) ; 
 size_t IPW_SCAN_ACTIVE_BROADCAST_AND_DIRECT_SCAN ; 
 size_t IPW_SCAN_ACTIVE_BROADCAST_SCAN ; 
 size_t IPW_SCAN_ACTIVE_DIRECT_SCAN ; 
 int /*<<< orphan*/  IPW_SCAN_CHECK_WATCHDOG ; 
 size_t IPW_SCAN_PASSIVE_FULL_DWELL_SCAN ; 
 scalar_t__ IW_MODE_MONITOR ; 
 int IW_SCAN_TYPE_PASSIVE ; 
#define  LIBIPW_24GHZ_BAND 129 
#define  LIBIPW_52GHZ_BAND 128 
 int STATUS_ASSOCIATED ; 
 int STATUS_DIRECT_SCAN_PENDING ; 
 int STATUS_EXIT_PENDING ; 
 int STATUS_INIT ; 
 int STATUS_RF_KILL_MASK ; 
 int STATUS_ROAMING ; 
 int STATUS_SCANNING ; 
 int STATUS_SCAN_ABORTING ; 
 int STATUS_SCAN_FORCED ; 
 int STATUS_SCAN_PENDING ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipw_add_scan_channels (struct ipw_priv*,struct ipw_scan_request_ext*,int) ; 
 int ipw_passive_dwell_time (struct ipw_priv*) ; 
 int ipw_send_scan_request_ext (struct ipw_priv*,struct ipw_scan_request_ext*) ; 
 int ipw_send_ssid (struct ipw_priv*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ipw_set_scan_type (struct ipw_scan_request_ext*,int,size_t) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libipw_get_scans (TYPE_1__*) ; 
 int libipw_is_valid_channel (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (struct ipw_scan_request_ext*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipw_request_scan_helper(struct ipw_priv *priv, int type, int direct)
{
	struct ipw_scan_request_ext scan;
	int err = 0, scan_type;

	if (!(priv->status & STATUS_INIT) ||
	    (priv->status & STATUS_EXIT_PENDING))
		return 0;

	mutex_lock(&priv->mutex);

	if (direct && (priv->direct_scan_ssid_len == 0)) {
		IPW_DEBUG_HC("Direct scan requested but no SSID to scan for\n");
		priv->status &= ~STATUS_DIRECT_SCAN_PENDING;
		goto done;
	}

	if (priv->status & STATUS_SCANNING) {
		IPW_DEBUG_HC("Concurrent scan requested.  Queuing.\n");
		priv->status |= direct ? STATUS_DIRECT_SCAN_PENDING :
					STATUS_SCAN_PENDING;
		goto done;
	}

	if (!(priv->status & STATUS_SCAN_FORCED) &&
	    priv->status & STATUS_SCAN_ABORTING) {
		IPW_DEBUG_HC("Scan request while abort pending.  Queuing.\n");
		priv->status |= direct ? STATUS_DIRECT_SCAN_PENDING :
					STATUS_SCAN_PENDING;
		goto done;
	}

	if (priv->status & STATUS_RF_KILL_MASK) {
		IPW_DEBUG_HC("Queuing scan due to RF Kill activation\n");
		priv->status |= direct ? STATUS_DIRECT_SCAN_PENDING :
					STATUS_SCAN_PENDING;
		goto done;
	}

	memset(&scan, 0, sizeof(scan));
	scan.full_scan_index = cpu_to_le32(libipw_get_scans(priv->ieee));

	if (type == IW_SCAN_TYPE_PASSIVE) {
		IPW_DEBUG_WX("use passive scanning\n");
		scan_type = IPW_SCAN_PASSIVE_FULL_DWELL_SCAN;
		scan.dwell_time[IPW_SCAN_PASSIVE_FULL_DWELL_SCAN] =
			cpu_to_le16(ipw_passive_dwell_time(priv));
		ipw_add_scan_channels(priv, &scan, scan_type);
		goto send_request;
	}

	/* Use active scan by default. */
	if (priv->config & CFG_SPEED_SCAN)
		scan.dwell_time[IPW_SCAN_ACTIVE_BROADCAST_SCAN] =
			cpu_to_le16(30);
	else
		scan.dwell_time[IPW_SCAN_ACTIVE_BROADCAST_SCAN] =
			cpu_to_le16(20);

	scan.dwell_time[IPW_SCAN_ACTIVE_BROADCAST_AND_DIRECT_SCAN] =
		cpu_to_le16(20);

	scan.dwell_time[IPW_SCAN_PASSIVE_FULL_DWELL_SCAN] =
		cpu_to_le16(ipw_passive_dwell_time(priv));
	scan.dwell_time[IPW_SCAN_ACTIVE_DIRECT_SCAN] = cpu_to_le16(20);

#ifdef CONFIG_IPW2200_MONITOR
	if (priv->ieee->iw_mode == IW_MODE_MONITOR) {
		u8 channel;
		u8 band = 0;

		switch (libipw_is_valid_channel(priv->ieee, priv->channel)) {
		case LIBIPW_52GHZ_BAND:
			band = (u8) (IPW_A_MODE << 6) | 1;
			channel = priv->channel;
			break;

		case LIBIPW_24GHZ_BAND:
			band = (u8) (IPW_B_MODE << 6) | 1;
			channel = priv->channel;
			break;

		default:
			band = (u8) (IPW_B_MODE << 6) | 1;
			channel = 9;
			break;
		}

		scan.channels_list[0] = band;
		scan.channels_list[1] = channel;
		ipw_set_scan_type(&scan, 1, IPW_SCAN_PASSIVE_FULL_DWELL_SCAN);

		/* NOTE:  The card will sit on this channel for this time
		 * period.  Scan aborts are timing sensitive and frequently
		 * result in firmware restarts.  As such, it is best to
		 * set a small dwell_time here and just keep re-issuing
		 * scans.  Otherwise fast channel hopping will not actually
		 * hop channels.
		 *
		 * TODO: Move SPEED SCAN support to all modes and bands */
		scan.dwell_time[IPW_SCAN_PASSIVE_FULL_DWELL_SCAN] =
			cpu_to_le16(2000);
	} else {
#endif				/* CONFIG_IPW2200_MONITOR */
		/* Honor direct scans first, otherwise if we are roaming make
		 * this a direct scan for the current network.  Finally,
		 * ensure that every other scan is a fast channel hop scan */
		if (direct) {
			err = ipw_send_ssid(priv, priv->direct_scan_ssid,
			                    priv->direct_scan_ssid_len);
			if (err) {
				IPW_DEBUG_HC("Attempt to send SSID command  "
					     "failed\n");
				goto done;
			}

			scan_type = IPW_SCAN_ACTIVE_BROADCAST_AND_DIRECT_SCAN;
		} else if ((priv->status & STATUS_ROAMING)
			   || (!(priv->status & STATUS_ASSOCIATED)
			       && (priv->config & CFG_STATIC_ESSID)
			       && (le32_to_cpu(scan.full_scan_index) % 2))) {
			err = ipw_send_ssid(priv, priv->essid, priv->essid_len);
			if (err) {
				IPW_DEBUG_HC("Attempt to send SSID command "
					     "failed.\n");
				goto done;
			}

			scan_type = IPW_SCAN_ACTIVE_BROADCAST_AND_DIRECT_SCAN;
		} else
			scan_type = IPW_SCAN_ACTIVE_BROADCAST_SCAN;

		ipw_add_scan_channels(priv, &scan, scan_type);
#ifdef CONFIG_IPW2200_MONITOR
	}
#endif

send_request:
	err = ipw_send_scan_request_ext(priv, &scan);
	if (err) {
		IPW_DEBUG_HC("Sending scan command failed: %08X\n", err);
		goto done;
	}

	priv->status |= STATUS_SCANNING;
	if (direct) {
		priv->status &= ~STATUS_DIRECT_SCAN_PENDING;
		priv->direct_scan_ssid_len = 0;
	} else
		priv->status &= ~STATUS_SCAN_PENDING;

	schedule_delayed_work(&priv->scan_check, IPW_SCAN_CHECK_WATCHDOG);
done:
	mutex_unlock(&priv->mutex);
	return err;
}