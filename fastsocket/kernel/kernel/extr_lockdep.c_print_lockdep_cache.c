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
struct lockdep_map {char* name; TYPE_1__* key; } ;
struct TYPE_2__ {int /*<<< orphan*/  subkeys; } ;

/* Variables and functions */
 int KSYM_NAME_LEN ; 
 char* __get_key_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  printk (char*,char const*) ; 

__attribute__((used)) static void print_lockdep_cache(struct lockdep_map *lock)
{
	const char *name;
	char str[KSYM_NAME_LEN];

	name = lock->name;
	if (!name)
		name = __get_key_name(lock->key->subkeys, str);

	printk("%s", name);
}