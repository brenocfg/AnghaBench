#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int spy_number; int /*<<< orphan*/  spy_stat; struct sockaddr** spy_address; } ;
typedef  TYPE_1__ wlandevice_t ;
struct sockaddr {char* sa_data; } ;
struct iw_request_info {int dummy; } ;
struct iw_quality {int dummy; } ;
struct iw_point {int length; } ;
struct TYPE_5__ {TYPE_1__* ml_priv; } ;
typedef  TYPE_2__ netdevice_t ;

/* Variables and functions */
 int ETH_ALEN ; 
 int IW_MAX_SPY ; 
 int /*<<< orphan*/  memcpy (struct sockaddr*,char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int p80211wext_siwspy(netdevice_t *dev,
			     struct iw_request_info *info,
			     struct iw_point *srq, char *extra)
{
	wlandevice_t *wlandev = dev->ml_priv;
	struct sockaddr address[IW_MAX_SPY];
	int number = srq->length;
	int i;

	/* Copy the data from the input buffer */
	memcpy(address, extra, sizeof(struct sockaddr) * number);

	wlandev->spy_number = 0;

	if (number > 0) {

		/* extract the addresses */
		for (i = 0; i < number; i++) {

			memcpy(wlandev->spy_address[i], address[i].sa_data,
			       ETH_ALEN);
		}

		/* reset stats */
		memset(wlandev->spy_stat, 0,
		       sizeof(struct iw_quality) * IW_MAX_SPY);

		/* set number of addresses */
		wlandev->spy_number = number;
	}

	return 0;
}