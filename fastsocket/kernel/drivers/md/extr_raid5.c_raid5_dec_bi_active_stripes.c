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
struct bio {int /*<<< orphan*/  bi_phys_segments; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int atomic_sub_return (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int raid5_dec_bi_active_stripes(struct bio *bio)
{
	atomic_t *segments = (atomic_t *)&bio->bi_phys_segments;
	return atomic_sub_return(1, segments) & 0xffff;
}