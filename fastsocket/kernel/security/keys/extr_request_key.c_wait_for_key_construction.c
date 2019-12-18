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
struct TYPE_2__ {scalar_t__* x; } ;
struct key {TYPE_1__ type_data; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_FLAG_NEGATIVE ; 
 int /*<<< orphan*/  KEY_FLAG_USER_CONSTRUCT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int key_validate (struct key*) ; 
 int /*<<< orphan*/  key_wait_bit ; 
 int /*<<< orphan*/  key_wait_bit_intr ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wait_for_key_construction(struct key *key, bool intr)
{
	int ret;

	ret = wait_on_bit(&key->flags, KEY_FLAG_USER_CONSTRUCT,
			  intr ? key_wait_bit_intr : key_wait_bit,
			  intr ? TASK_INTERRUPTIBLE : TASK_UNINTERRUPTIBLE);
	if (ret < 0)
		return ret;
	if (test_bit(KEY_FLAG_NEGATIVE, &key->flags)) {
		smp_rmb();
		return (long)key->type_data.x[0];
	}
	return key_validate(key);
}