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
struct bitmap_port {int /*<<< orphan*/  memsize; int /*<<< orphan*/  members; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bitmap_port_flush(struct ip_set *set)
{
	struct bitmap_port *map = set->data;

	memset(map->members, 0, map->memsize);
}