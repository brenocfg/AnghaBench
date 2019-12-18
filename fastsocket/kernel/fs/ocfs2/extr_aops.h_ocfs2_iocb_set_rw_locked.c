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
struct kiocb {int /*<<< orphan*/  private; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int,unsigned long*) ; 
 int /*<<< orphan*/  set_bit (int,unsigned long*) ; 

__attribute__((used)) static inline void ocfs2_iocb_set_rw_locked(struct kiocb *iocb, int level)
{
	set_bit(0, (unsigned long *)&iocb->private);
	if (level)
		set_bit(1, (unsigned long *)&iocb->private);
	else
		clear_bit(1, (unsigned long *)&iocb->private);
}