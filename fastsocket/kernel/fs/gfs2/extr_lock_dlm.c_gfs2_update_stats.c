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
struct gfs2_lkstats {int* stats; } ;
typedef  int s64 ;

/* Variables and functions */
 int abs64 (int) ; 

__attribute__((used)) static inline void gfs2_update_stats(struct gfs2_lkstats *s, unsigned index,
				     s64 sample)
{
	s64 delta = sample - s->stats[index];
	s->stats[index] += (delta >> 3);
	index++;
	s->stats[index] += ((abs64(delta) - s->stats[index]) >> 2);
}