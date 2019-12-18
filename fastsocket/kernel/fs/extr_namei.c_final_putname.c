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
struct filename {struct filename* name; scalar_t__ separate; } ;

/* Variables and functions */
 int /*<<< orphan*/  __putname (struct filename*) ; 
 int /*<<< orphan*/  kfree (struct filename*) ; 

void final_putname(struct filename *name)
{
	if (name->separate) {
		__putname(name->name);
		kfree(name);
	} else {
		__putname(name);
	}
}