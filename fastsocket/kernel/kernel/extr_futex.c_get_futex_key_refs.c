#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_4__* mm; } ;
struct TYPE_8__ {TYPE_2__* inode; } ;
struct TYPE_6__ {int offset; int /*<<< orphan*/  ptr; } ;
union futex_key {TYPE_5__ private; TYPE_3__ shared; TYPE_1__ both; } ;
struct TYPE_9__ {int /*<<< orphan*/  mm_count; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_count; } ;

/* Variables and functions */
#define  FUT_OFF_INODE 129 
#define  FUT_OFF_MMSHARED 128 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void get_futex_key_refs(union futex_key *key)
{
	if (!key->both.ptr)
		return;

	switch (key->both.offset & (FUT_OFF_INODE|FUT_OFF_MMSHARED)) {
	case FUT_OFF_INODE:
		atomic_inc(&key->shared.inode->i_count);
		break;
	case FUT_OFF_MMSHARED:
		atomic_inc(&key->private.mm->mm_count);
		break;
	}
}