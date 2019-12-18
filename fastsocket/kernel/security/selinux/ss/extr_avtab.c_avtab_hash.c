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
typedef  int u16 ;
struct avtab_key {int target_class; int target_type; int source_type; } ;

/* Variables and functions */

__attribute__((used)) static inline int avtab_hash(struct avtab_key *keyp, u16 mask)
{
	return ((keyp->target_class + (keyp->target_type << 2) +
		 (keyp->source_type << 9)) & mask);
}