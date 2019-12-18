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
struct brr_to_sig_map {int brr_mask; unsigned long tbr_tt; int signo; } ;

/* Variables and functions */
 unsigned long BRR_EBTT ; 
 struct brr_to_sig_map* brr_to_sig_map ; 

__attribute__((used)) static inline int gdbstub_compute_signal(unsigned long brr)
{
	const struct brr_to_sig_map *map;
	unsigned long tbr = (brr & BRR_EBTT) >> 12;

	for (map = brr_to_sig_map; map->brr_mask; map++)
		if (map->brr_mask & brr)
			if (!map->tbr_tt || map->tbr_tt == tbr)
				break;

	return map->signo;
}