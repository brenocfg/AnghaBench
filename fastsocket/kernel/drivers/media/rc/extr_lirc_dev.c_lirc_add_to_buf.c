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
struct TYPE_2__ {int (* add_to_buf ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; } ;
struct irctl {int /*<<< orphan*/  task; int /*<<< orphan*/  buf; TYPE_1__ d; } ;

/* Variables and functions */
 int ENODATA ; 
 int ENODEV ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lirc_add_to_buf(struct irctl *ir)
{
	if (ir->d.add_to_buf) {
		int res = -ENODATA;
		int got_data = 0;

		/*
		 * service the device as long as it is returning
		 * data and we have space
		 */
get_data:
		res = ir->d.add_to_buf(ir->d.data, ir->buf);
		if (res == 0) {
			got_data++;
			goto get_data;
		}

		if (res == -ENODEV)
			kthread_stop(ir->task);

		return got_data ? 0 : res;
	}

	return 0;
}