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
struct uio_map {int dummy; } ;
struct kobject {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct uio_map*) ; 
 struct uio_map* to_map (struct kobject*) ; 

__attribute__((used)) static void map_release(struct kobject *kobj)
{
	struct uio_map *map = to_map(kobj);
	kfree(map);
}