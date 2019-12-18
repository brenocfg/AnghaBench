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
struct sctp_auth_bytes {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_DBG_OBJCNT_DEC (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  keys ; 
 int /*<<< orphan*/  kfree (struct sctp_auth_bytes*) ; 

void sctp_auth_key_put(struct sctp_auth_bytes *key)
{
	if (!key)
		return;

	if (atomic_dec_and_test(&key->refcnt)) {
		kfree(key);
		SCTP_DBG_OBJCNT_DEC(keys);
	}
}