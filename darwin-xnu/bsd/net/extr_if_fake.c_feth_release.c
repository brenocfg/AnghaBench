#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  TYPE_1__* if_fake_ref ;
struct TYPE_4__ {int /*<<< orphan*/  iff_retain_count; } ;

/* Variables and functions */
 int OSDecrementAtomic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  feth_free (TYPE_1__*) ; 

__attribute__((used)) static void
feth_release(if_fake_ref fakeif)
{
	u_int32_t		old_retain_count;

	old_retain_count = OSDecrementAtomic(&fakeif->iff_retain_count);
	switch (old_retain_count) {
	case 0:
		assert(old_retain_count != 0);
		break;
	case 1:
		feth_free(fakeif);
		break;
	default:
		break;
	}
	return;
}