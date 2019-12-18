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
struct serio_raw {scalar_t__ refcnt; int /*<<< orphan*/  node; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct serio_raw*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int serio_raw_cleanup(struct serio_raw *serio_raw)
{
	if (--serio_raw->refcnt == 0) {
		misc_deregister(&serio_raw->dev);
		list_del_init(&serio_raw->node);
		kfree(serio_raw);

		return 1;
	}

	return 0;
}