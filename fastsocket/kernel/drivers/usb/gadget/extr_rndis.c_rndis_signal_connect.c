#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  media_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_MEDIA_STATE_CONNECTED ; 
 int /*<<< orphan*/  RNDIS_STATUS_MEDIA_CONNECT ; 
 int rndis_indicate_status_msg (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* rndis_per_dev_params ; 

int rndis_signal_connect (int configNr)
{
	rndis_per_dev_params [configNr].media_state
			= NDIS_MEDIA_STATE_CONNECTED;
	return rndis_indicate_status_msg (configNr,
					  RNDIS_STATUS_MEDIA_CONNECT);
}