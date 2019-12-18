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
struct slabinfo {char* name; } ;

/* Variables and functions */
 char* buffer ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ read_slab_obj (struct slabinfo*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void ops(struct slabinfo *s)
{
	if (strcmp(s->name, "*") == 0)
		return;

	if (read_slab_obj(s, "ops")) {
		printf("\n%s: kmem_cache operations\n", s->name);
		printf("--------------------------------------------\n");
		printf(buffer);
	} else
		printf("\n%s has no kmem_cache operations\n", s->name);
}