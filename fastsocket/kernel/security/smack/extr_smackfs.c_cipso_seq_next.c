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
struct seq_file {int dummy; } ;
struct list_head {void* next; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_READ_FINISHED ; 
 scalar_t__ list_is_last (struct list_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smack_known_list ; 

__attribute__((used)) static void *cipso_seq_next(struct seq_file *s, void *v, loff_t *pos)
{
	struct list_head  *list = v;

	/*
	 * labels with no associated cipso value wont be printed
	 * in cipso_seq_show
	 */
	if (list_is_last(list, &smack_known_list)) {
		*pos = SEQ_READ_FINISHED;
		return NULL;
	}

	return list->next;
}