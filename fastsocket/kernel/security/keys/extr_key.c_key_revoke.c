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
typedef  scalar_t__ time_t ;
struct timespec {scalar_t__ tv_sec; } ;
struct key {scalar_t__ revoked_at; int /*<<< orphan*/  sem; TYPE_1__* type; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* revoke ) (struct key*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_FLAG_REVOKED ; 
 struct timespec current_kernel_time () ; 
 int /*<<< orphan*/  down_write_nested (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  key_check (struct key*) ; 
 scalar_t__ key_gc_delay ; 
 int /*<<< orphan*/  key_schedule_gc (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct key*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void key_revoke(struct key *key)
{
	struct timespec now;
	time_t time;

	key_check(key);

	/* make sure no one's trying to change or use the key when we mark it
	 * - we tell lockdep that we might nest because we might be revoking an
	 *   authorisation key whilst holding the sem on a key we've just
	 *   instantiated
	 */
	down_write_nested(&key->sem, 1);
	if (!test_and_set_bit(KEY_FLAG_REVOKED, &key->flags) &&
	    key->type->revoke)
		key->type->revoke(key);

	/* set the death time to no more than the expiry time */
	now = current_kernel_time();
	time = now.tv_sec;
	if (key->revoked_at == 0 || key->revoked_at > time) {
		key->revoked_at = time;
		key_schedule_gc(key->revoked_at + key_gc_delay);
	}

	up_write(&key->sem);
}