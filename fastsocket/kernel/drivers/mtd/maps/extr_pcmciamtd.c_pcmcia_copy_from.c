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
struct map_info {int /*<<< orphan*/  map_priv_2; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG (int,char*,void*,unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ DEV_REMOVED (struct map_info*) ; 
 int /*<<< orphan*/  memcpy_fromio (void*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcmcia_copy_from(struct map_info *map, void *to, unsigned long from, ssize_t len)
{
	caddr_t win_base = (caddr_t)map->map_priv_2;

	if(DEV_REMOVED(map))
		return;

	DEBUG(3, "to = %p from = %lu len = %u", to, from, len);
	memcpy_fromio(to, win_base + from, len);
}