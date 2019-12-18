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
struct symtab {scalar_t__ nprim; int /*<<< orphan*/  table; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  hashtab_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  symcmp ; 
 int /*<<< orphan*/  symhash ; 

int symtab_init(struct symtab *s, unsigned int size)
{
	s->table = hashtab_create(symhash, symcmp, size);
	if (!s->table)
		return -ENOMEM;
	s->nprim = 0;
	return 0;
}