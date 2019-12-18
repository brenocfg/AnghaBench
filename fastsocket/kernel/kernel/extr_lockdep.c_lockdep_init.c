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

/* Variables and functions */
 int CHAINHASH_SIZE ; 
 int CLASSHASH_SIZE ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (scalar_t__) ; 
 scalar_t__ chainhash_table ; 
 scalar_t__ classhash_table ; 
 int lockdep_initialized ; 

void lockdep_init(void)
{
	int i;

	/*
	 * Some architectures have their own start_kernel()
	 * code which calls lockdep_init(), while we also
	 * call lockdep_init() from the start_kernel() itself,
	 * and we want to initialize the hashes only once:
	 */
	if (lockdep_initialized)
		return;

	for (i = 0; i < CLASSHASH_SIZE; i++)
		INIT_LIST_HEAD(classhash_table + i);

	for (i = 0; i < CHAINHASH_SIZE; i++)
		INIT_LIST_HEAD(chainhash_table + i);

	lockdep_initialized = 1;
}