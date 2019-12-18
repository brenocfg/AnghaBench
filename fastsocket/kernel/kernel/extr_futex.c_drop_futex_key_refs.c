#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mm; } ;
struct TYPE_5__ {int /*<<< orphan*/  inode; } ;
struct TYPE_4__ {int offset; int /*<<< orphan*/  ptr; } ;
union futex_key {TYPE_3__ private; TYPE_2__ shared; TYPE_1__ both; } ;

/* Variables and functions */
#define  FUT_OFF_INODE 129 
#define  FUT_OFF_MMSHARED 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmdrop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void drop_futex_key_refs(union futex_key *key)
{
	if (!key->both.ptr) {
		/* If we're here then we tried to put a key we failed to get */
		WARN_ON_ONCE(1);
		return;
	}

	switch (key->both.offset & (FUT_OFF_INODE|FUT_OFF_MMSHARED)) {
	case FUT_OFF_INODE:
		iput(key->shared.inode);
		break;
	case FUT_OFF_MMSHARED:
		mmdrop(key->private.mm);
		break;
	}
}