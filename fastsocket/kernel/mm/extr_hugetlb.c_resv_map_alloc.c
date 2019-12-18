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
struct resv_map {int /*<<< orphan*/  regions; int /*<<< orphan*/  refs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct resv_map* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct resv_map *resv_map_alloc(void)
{
	struct resv_map *resv_map = kmalloc(sizeof(*resv_map), GFP_KERNEL);
	if (!resv_map)
		return NULL;

	kref_init(&resv_map->refs);
	INIT_LIST_HEAD(&resv_map->regions);

	return resv_map;
}