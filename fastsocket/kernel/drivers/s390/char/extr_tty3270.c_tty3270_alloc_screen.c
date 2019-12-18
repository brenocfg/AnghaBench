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
struct tty3270_line {int dummy; } ;
struct tty3270_cell {int dummy; } ;
struct TYPE_3__ {int rows; int cols; } ;
struct tty3270 {TYPE_2__* screen; TYPE_1__ view; } ;
struct TYPE_4__ {struct TYPE_4__* cells; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 void* kzalloc (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
tty3270_alloc_screen(struct tty3270 *tp)
{
	unsigned long size;
	int lines;

	size = sizeof(struct tty3270_line) * (tp->view.rows - 2);
	tp->screen = kzalloc(size, GFP_KERNEL);
	if (!tp->screen)
		goto out_err;
	for (lines = 0; lines < tp->view.rows - 2; lines++) {
		size = sizeof(struct tty3270_cell) * tp->view.cols;
		tp->screen[lines].cells = kzalloc(size, GFP_KERNEL);
		if (!tp->screen[lines].cells)
			goto out_screen;
	}
	return 0;
out_screen:
	while (lines--)
		kfree(tp->screen[lines].cells);
	kfree(tp->screen);
out_err:
	return -ENOMEM;
}