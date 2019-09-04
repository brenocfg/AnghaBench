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
typedef  size_t uint32_t ;
struct dso {size_t* hashtab; size_t* ghashtab; } ;

/* Variables and functions */

__attribute__((used)) static size_t count_syms(struct dso *p)
{
	if (p->hashtab) return p->hashtab[1];

	size_t nsym, i;
	uint32_t *buckets = p->ghashtab + 4 + (p->ghashtab[2]*sizeof(size_t)/4);
	uint32_t *hashval;
	for (i = nsym = 0; i < p->ghashtab[0]; i++) {
		if (buckets[i] > nsym)
			nsym = buckets[i];
	}
	if (nsym) {
		hashval = buckets + p->ghashtab[0] + (nsym - p->ghashtab[1]);
		do nsym++;
		while (!(*hashval++ & 1));
	}
	return nsym;
}