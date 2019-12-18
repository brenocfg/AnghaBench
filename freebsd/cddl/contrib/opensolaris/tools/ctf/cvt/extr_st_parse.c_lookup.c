#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int t_id; struct TYPE_4__* t_hash; } ;
typedef  TYPE_1__ tdesc_t ;

/* Variables and functions */
 int HASH (int) ; 
 TYPE_1__** hash_table ; 

tdesc_t *
lookup(int h)
{
	int bucket = HASH(h);
	tdesc_t *tdp = hash_table[bucket];

	while (tdp != NULL) {
		if (tdp->t_id == h)
			return (tdp);
		tdp = tdp->t_hash;
	}
	return (NULL);
}