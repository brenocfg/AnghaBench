#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct key_construction {TYPE_1__* authkey; TYPE_1__* key; } ;
struct TYPE_5__ {int /*<<< orphan*/  serial; } ;

/* Variables and functions */
 int /*<<< orphan*/  kenter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  key_negate_and_link (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  key_negative_timeout ; 
 int /*<<< orphan*/  key_put (TYPE_1__*) ; 
 int /*<<< orphan*/  key_revoke (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct key_construction*) ; 

void complete_request_key(struct key_construction *cons, int error)
{
	kenter("{%d,%d},%d", cons->key->serial, cons->authkey->serial, error);

	if (error < 0)
		key_negate_and_link(cons->key, key_negative_timeout, NULL,
				    cons->authkey);
	else
		key_revoke(cons->authkey);

	key_put(cons->key);
	key_put(cons->authkey);
	kfree(cons);
}