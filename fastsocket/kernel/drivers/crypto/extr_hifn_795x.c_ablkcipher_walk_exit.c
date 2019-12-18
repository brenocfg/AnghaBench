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
struct scatterlist {scalar_t__ length; } ;
struct ablkcipher_walk {int num; struct scatterlist* cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  __free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 

__attribute__((used)) static void ablkcipher_walk_exit(struct ablkcipher_walk *w)
{
	int i;

	for (i=0; i<w->num; ++i) {
		struct scatterlist *s = &w->cache[i];

		__free_page(sg_page(s));

		s->length = 0;
	}

	w->num = 0;
}