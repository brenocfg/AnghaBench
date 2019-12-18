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
struct ip_set {struct bitmap_port* data; } ;
struct bitmap_port {int /*<<< orphan*/  members; int /*<<< orphan*/  gc; int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_set_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bitmap_port*) ; 
 scalar_t__ with_timeout (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bitmap_port_destroy(struct ip_set *set)
{
	struct bitmap_port *map = set->data;

	if (with_timeout(map->timeout))
		del_timer_sync(&map->gc);

	ip_set_free(map->members);
	kfree(map);

	set->data = NULL;
}