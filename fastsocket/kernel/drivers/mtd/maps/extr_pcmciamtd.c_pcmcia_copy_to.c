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
 int /*<<< orphan*/  DEBUG (int,char*,unsigned long,void const*,int /*<<< orphan*/ ) ; 
 scalar_t__ DEV_REMOVED (struct map_info*) ; 
 int /*<<< orphan*/  memcpy_toio (scalar_t__,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcmcia_copy_to(struct map_info *map, unsigned long to, const void *from, ssize_t len)
{
	caddr_t win_base = (caddr_t)map->map_priv_2;

	if(DEV_REMOVED(map))
		return;

	DEBUG(3, "to = %lu from = %p len = %u", to, from, len);
	memcpy_toio(win_base + to, from, len);
}