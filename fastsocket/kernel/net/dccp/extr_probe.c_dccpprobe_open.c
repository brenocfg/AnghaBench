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
struct inode {int dummy; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tstart; int /*<<< orphan*/  fifo; } ;

/* Variables and functions */
 TYPE_1__ dccpw ; 
 int /*<<< orphan*/  getnstimeofday (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dccpprobe_open(struct inode *inode, struct file *file)
{
	kfifo_reset(dccpw.fifo);
	getnstimeofday(&dccpw.tstart);
	return 0;
}