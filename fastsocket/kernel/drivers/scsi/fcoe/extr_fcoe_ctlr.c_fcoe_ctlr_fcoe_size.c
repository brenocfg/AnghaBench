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
typedef  scalar_t__ u32 ;
struct fcoe_hdr {int dummy; } ;
struct fcoe_ctlr {TYPE_1__* lp; } ;
struct fcoe_crc_eof {int dummy; } ;
struct fc_frame_header {int dummy; } ;
struct TYPE_2__ {scalar_t__ mfs; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 fcoe_ctlr_fcoe_size(struct fcoe_ctlr *fip)
{
	/*
	 * Determine the max FCoE frame size allowed, including
	 * FCoE header and trailer.
	 * Note:  lp->mfs is currently the payload size, not the frame size.
	 */
	return fip->lp->mfs + sizeof(struct fc_frame_header) +
		sizeof(struct fcoe_hdr) + sizeof(struct fcoe_crc_eof);
}