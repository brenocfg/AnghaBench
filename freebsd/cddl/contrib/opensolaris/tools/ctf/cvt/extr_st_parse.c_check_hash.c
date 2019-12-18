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
struct TYPE_4__ {struct TYPE_4__* t_next; struct TYPE_4__* t_hash; } ;
typedef  TYPE_1__ tdesc_t ;

/* Variables and functions */
 int BUCKETS ; 
 TYPE_1__** hash_table ; 
 TYPE_1__** name_table ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  terminate (char*,int) ; 

void
check_hash(void)
{
	tdesc_t *tdp;
	int i;

	printf("checking hash\n");
	for (i = 0; i < BUCKETS; i++) {
		if (hash_table[i]) {
			for (tdp = hash_table[i]->t_hash;
			    tdp && tdp != hash_table[i];
			    tdp = tdp->t_hash)
				continue;
			if (tdp) {
				terminate("cycle in hash bucket %d\n", i);
				return;
			}
		}

		if (name_table[i]) {
			for (tdp = name_table[i]->t_next;
			    tdp && tdp != name_table[i];
			    tdp = tdp->t_next)
				continue;
			if (tdp) {
				terminate("cycle in name bucket %d\n", i);
				return;
			}
		}
	}
	printf("done\n");
}