#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_4__ {scalar_t__ tr_idx; } ;
struct TYPE_3__ {scalar_t__ tr_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  cycle_kernel_lock () ; 
 TYPE_2__ rx_ring ; 
 TYPE_1__ tx_ring ; 

__attribute__((used)) static int tgt_open(struct inode *inode, struct file *file)
{
	tx_ring.tr_idx = rx_ring.tr_idx = 0;

	cycle_kernel_lock();
	return 0;
}