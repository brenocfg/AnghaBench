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
struct r1conf {int /*<<< orphan*/  wait_barrier; } ;
struct mddev {struct r1conf* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  lower_barrier (struct r1conf*) ; 
 int /*<<< orphan*/  raise_barrier (struct r1conf*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void raid1_quiesce(struct mddev *mddev, int state)
{
	struct r1conf *conf = mddev->private;

	switch(state) {
	case 2: /* wake for suspend */
		wake_up(&conf->wait_barrier);
		break;
	case 1:
		raise_barrier(conf);
		break;
	case 0:
		lower_barrier(conf);
		break;
	}
}