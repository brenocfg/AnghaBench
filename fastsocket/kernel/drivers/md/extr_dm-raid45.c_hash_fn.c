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
struct stripe_hash {int prime; int shift; int mask; } ;
typedef  int sector_t ;

/* Variables and functions */

__attribute__((used)) static unsigned hash_fn(struct stripe_hash *hash, sector_t key)
{
	return (unsigned) (((key * hash->prime) >> hash->shift) & hash->mask);
}