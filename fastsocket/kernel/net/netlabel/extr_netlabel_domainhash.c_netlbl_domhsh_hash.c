#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  netlbl_domhsh ; 
 TYPE_1__* rcu_dereference (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 

__attribute__((used)) static u32 netlbl_domhsh_hash(const char *key)
{
	u32 iter;
	u32 val;
	u32 len;

	/* This is taken (with slight modification) from
	 * security/selinux/ss/symtab.c:symhash() */

	for (iter = 0, val = 0, len = strlen(key); iter < len; iter++)
		val = (val << 4 | (val >> (8 * sizeof(u32) - 4))) ^ key[iter];
	return val & (rcu_dereference(netlbl_domhsh)->size - 1);
}