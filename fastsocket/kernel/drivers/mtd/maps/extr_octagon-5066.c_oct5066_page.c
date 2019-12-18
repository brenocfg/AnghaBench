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
struct map_info {unsigned long map_priv_1; } ;
typedef  scalar_t__ __u8 ;

/* Variables and functions */
 unsigned long WINDOW_SHIFT ; 
 int /*<<< orphan*/  __oct5066_page (struct map_info*,scalar_t__) ; 
 scalar_t__ page_n_dev ; 

__attribute__((used)) static inline void oct5066_page(struct map_info *map, unsigned long ofs)
{
	__u8 byte = map->map_priv_1 | (ofs >> WINDOW_SHIFT);

	if (page_n_dev != byte)
		__oct5066_page(map, byte);
}