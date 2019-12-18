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
struct ioctl_trans {struct ioctl_trans* next; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 unsigned long ioctl32_hash (int /*<<< orphan*/ ) ; 
 struct ioctl_trans** ioctl32_hash_table ; 

__attribute__((used)) static void ioctl32_insert_translation(struct ioctl_trans *trans)
{
	unsigned long hash;
	struct ioctl_trans *t;

	hash = ioctl32_hash (trans->cmd);
	if (!ioctl32_hash_table[hash])
		ioctl32_hash_table[hash] = trans;
	else {
		t = ioctl32_hash_table[hash];
		while (t->next)
			t = t->next;
		trans->next = NULL;
		t->next = trans;
	}
}