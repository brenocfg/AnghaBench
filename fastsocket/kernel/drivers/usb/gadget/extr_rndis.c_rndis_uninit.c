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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int RNDIS_MAX_CONFIGS ; 
 int /*<<< orphan*/  RNDIS_UNINITIALIZED ; 
 int /*<<< orphan*/  rndis_free_response (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rndis_get_next_response (int,int /*<<< orphan*/ *) ; 
 TYPE_1__* rndis_per_dev_params ; 

void rndis_uninit (int configNr)
{
	u8 *buf;
	u32 length;

	if (configNr >= RNDIS_MAX_CONFIGS)
		return;
	rndis_per_dev_params [configNr].state = RNDIS_UNINITIALIZED;

	/* drain the response queue */
	while ((buf = rndis_get_next_response(configNr, &length)))
		rndis_free_response(configNr, buf);
}