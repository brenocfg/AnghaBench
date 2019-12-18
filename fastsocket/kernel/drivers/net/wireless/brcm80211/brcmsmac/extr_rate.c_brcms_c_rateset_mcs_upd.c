#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
struct brcms_c_rateset {scalar_t__* mcs; } ;

/* Variables and functions */
 int MAX_STREAMS_SUPPORTED ; 

void brcms_c_rateset_mcs_upd(struct brcms_c_rateset *rs, u8 txstreams)
{
	int i;
	for (i = txstreams; i < MAX_STREAMS_SUPPORTED; i++)
		rs->mcs[i] = 0;
}