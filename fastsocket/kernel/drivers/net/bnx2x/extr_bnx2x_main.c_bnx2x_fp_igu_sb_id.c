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
typedef  scalar_t__ u8 ;
struct bnx2x_fastpath {TYPE_1__* bp; scalar_t__ index; } ;
struct TYPE_2__ {scalar_t__ igu_base_sb; } ;

/* Variables and functions */
 scalar_t__ CNIC_SUPPORT (TYPE_1__*) ; 

__attribute__((used)) static inline u8 bnx2x_fp_igu_sb_id(struct bnx2x_fastpath *fp)
{
	return fp->bp->igu_base_sb + fp->index + CNIC_SUPPORT(fp->bp);
}