#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ar4; } ;
struct TYPE_5__ {TYPE_1__ mm_segment; } ;
struct TYPE_6__ {TYPE_2__ thread; } ;

/* Variables and functions */
 scalar_t__ HOME_SPACE_MODE ; 
 TYPE_3__* current ; 
 scalar_t__ user_mode ; 

__attribute__((used)) static inline int user_space_fault(unsigned long trans_exc_code)
{
	/*
	 * The lowest two bits of the translation exception
	 * identification indicate which paging table was used.
	 */
	trans_exc_code &= 3;
	if (trans_exc_code == 2)
		/* Access via secondary space, set_fs setting decides */
		return current->thread.mm_segment.ar4;
	if (user_mode == HOME_SPACE_MODE)
		/* User space if the access has been done via home space. */
		return trans_exc_code == 3;
	/*
	 * If the user space is not the home space the kernel runs in home
	 * space. Access via secondary space has already been covered,
	 * access via primary space or access register is from user space
	 * and access via home space is from the kernel.
	 */
	return trans_exc_code != 3;
}