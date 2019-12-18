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
typedef  scalar_t__ u64 ;
struct tsb {int dummy; } ;
struct tcw {scalar_t__ tsb; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */

void tcw_set_tsb(struct tcw *tcw, struct tsb *tsb)
{
	tcw->tsb = (u64) ((addr_t) tsb);
}