#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ipw_priv {int status; int cmdlog_len; int config; int /*<<< orphan*/  request_scan; int /*<<< orphan*/  rf_kill; int /*<<< orphan*/  ieee; int /*<<< orphan*/ * eeprom; int /*<<< orphan*/  mac_addr; TYPE_1__* net_dev; int /*<<< orphan*/ * cmdlog; scalar_t__ suspend_time; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {int /*<<< orphan*/  perm_addr; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int CFG_CUSTOM_MAC ; 
 size_t EEPROM_COUNTRY_CODE ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*,int,...) ; 
 int /*<<< orphan*/  IPW_ERROR (char*,int) ; 
 int /*<<< orphan*/  IPW_WARNING (char*,...) ; 
 int MAX_HW_RESTARTS ; 
 int STATUS_EXIT_PENDING ; 
 int STATUS_RF_KILL_SW ; 
 int cmdlog ; 
 int /*<<< orphan*/  eeprom_parse_mac (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int ipw_config (struct ipw_priv*) ; 
 int /*<<< orphan*/  ipw_down (struct ipw_priv*) ; 
 TYPE_2__* ipw_geos ; 
 int /*<<< orphan*/  ipw_init_ordinals (struct ipw_priv*) ; 
 int ipw_load (struct ipw_priv*) ; 
 int /*<<< orphan*/ * kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  libipw_networks_age (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ libipw_set_geo (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ rf_kill_active (struct ipw_priv*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ipw_up(struct ipw_priv *priv)
{
	int rc, i, j;

	/* Age scan list entries found before suspend */
	if (priv->suspend_time) {
		libipw_networks_age(priv->ieee, priv->suspend_time);
		priv->suspend_time = 0;
	}

	if (priv->status & STATUS_EXIT_PENDING)
		return -EIO;

	if (cmdlog && !priv->cmdlog) {
		priv->cmdlog = kcalloc(cmdlog, sizeof(*priv->cmdlog),
				       GFP_KERNEL);
		if (priv->cmdlog == NULL) {
			IPW_ERROR("Error allocating %d command log entries.\n",
				  cmdlog);
			return -ENOMEM;
		} else {
			priv->cmdlog_len = cmdlog;
		}
	}

	for (i = 0; i < MAX_HW_RESTARTS; i++) {
		/* Load the microcode, firmware, and eeprom.
		 * Also start the clocks. */
		rc = ipw_load(priv);
		if (rc) {
			IPW_ERROR("Unable to load firmware: %d\n", rc);
			return rc;
		}

		ipw_init_ordinals(priv);
		if (!(priv->config & CFG_CUSTOM_MAC))
			eeprom_parse_mac(priv, priv->mac_addr);
		memcpy(priv->net_dev->dev_addr, priv->mac_addr, ETH_ALEN);
		memcpy(priv->net_dev->perm_addr, priv->mac_addr, ETH_ALEN);

		for (j = 0; j < ARRAY_SIZE(ipw_geos); j++) {
			if (!memcmp(&priv->eeprom[EEPROM_COUNTRY_CODE],
				    ipw_geos[j].name, 3))
				break;
		}
		if (j == ARRAY_SIZE(ipw_geos)) {
			IPW_WARNING("SKU [%c%c%c] not recognized.\n",
				    priv->eeprom[EEPROM_COUNTRY_CODE + 0],
				    priv->eeprom[EEPROM_COUNTRY_CODE + 1],
				    priv->eeprom[EEPROM_COUNTRY_CODE + 2]);
			j = 0;
		}
		if (libipw_set_geo(priv->ieee, &ipw_geos[j])) {
			IPW_WARNING("Could not set geography.");
			return 0;
		}

		if (priv->status & STATUS_RF_KILL_SW) {
			IPW_WARNING("Radio disabled by module parameter.\n");
			return 0;
		} else if (rf_kill_active(priv)) {
			IPW_WARNING("Radio Frequency Kill Switch is On:\n"
				    "Kill switch must be turned off for "
				    "wireless networking to work.\n");
			schedule_delayed_work(&priv->rf_kill, 2 * HZ);
			return 0;
		}

		rc = ipw_config(priv);
		if (!rc) {
			IPW_DEBUG_INFO("Configured device on count %i\n", i);

			/* If configure to try and auto-associate, kick
			 * off a scan. */
			schedule_delayed_work(&priv->request_scan, 0);

			return 0;
		}

		IPW_DEBUG_INFO("Device configuration failed: 0x%08X\n", rc);
		IPW_DEBUG_INFO("Failed to config device on retry %d of %d\n",
			       i, MAX_HW_RESTARTS);

		/* We had an error bringing up the hardware, so take it
		 * all the way back down so we can try again */
		ipw_down(priv);
	}

	/* tried to restart and config the device for as long as our
	 * patience could withstand */
	IPW_ERROR("Unable to initialize device after %d attempts.\n", i);

	return -EIO;
}