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
struct mddev {struct faulty_conf* private; } ;
struct faulty_conf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct faulty_conf*) ; 

__attribute__((used)) static int stop(struct mddev *mddev)
{
	struct faulty_conf *conf = mddev->private;

	kfree(conf);
	mddev->private = NULL;
	return 0;
}