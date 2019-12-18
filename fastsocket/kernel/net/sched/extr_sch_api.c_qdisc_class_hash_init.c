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
struct Qdisc_class_hash {unsigned int hashsize; unsigned int hashmask; scalar_t__ hashelems; int /*<<< orphan*/ * hash; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * qdisc_class_hash_alloc (unsigned int) ; 

int qdisc_class_hash_init(struct Qdisc_class_hash *clhash)
{
	unsigned int size = 4;

	clhash->hash = qdisc_class_hash_alloc(size);
	if (clhash->hash == NULL)
		return -ENOMEM;
	clhash->hashsize  = size;
	clhash->hashmask  = size - 1;
	clhash->hashelems = 0;
	return 0;
}