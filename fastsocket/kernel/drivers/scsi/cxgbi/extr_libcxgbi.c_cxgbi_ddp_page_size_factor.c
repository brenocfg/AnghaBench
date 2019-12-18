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

/* Variables and functions */
 int DDP_PGIDX_MAX ; 
 int* ddp_page_order ; 

void cxgbi_ddp_page_size_factor(int *pgsz_factor)
{
	int i;

	for (i = 0; i < DDP_PGIDX_MAX; i++)
		pgsz_factor[i] = ddp_page_order[i];
}