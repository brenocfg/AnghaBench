#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * binds; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ in_dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_unprobe (TYPE_1__*) ; 

__attribute__((used)) static void in_free(in_dev_t *dev)
{
	in_unprobe(dev);
	free(dev->name);
	dev->name = NULL;
	free(dev->binds);
	dev->binds = NULL;
}