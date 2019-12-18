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
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int KMMIO_PAGE_TABLE_SIZE ; 
 int /*<<< orphan*/ * kmmio_page_table ; 
 int /*<<< orphan*/  nb_die ; 
 int register_die_notifier (int /*<<< orphan*/ *) ; 

int kmmio_init(void)
{
	int i;

	for (i = 0; i < KMMIO_PAGE_TABLE_SIZE; i++)
		INIT_LIST_HEAD(&kmmio_page_table[i]);

	return register_die_notifier(&nb_die);
}