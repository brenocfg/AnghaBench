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
struct ksign_public_key {scalar_t__ expiredate; scalar_t__ timestamp; int /*<<< orphan*/  link; int /*<<< orphan*/  count; int /*<<< orphan*/ * keyid; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ get_seconds () ; 
 int /*<<< orphan*/  keyring ; 
 int /*<<< orphan*/  keyring_sem ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_keyblock_key(struct ksign_public_key *pk, void *data)
{
	printk("- Added public key %X%X\n", pk->keyid[0], pk->keyid[1]);

	if (pk->expiredate && pk->expiredate < get_seconds())
		printk("  - public key has expired\n");

	if (pk->timestamp > get_seconds())
		printk("  - key was been created %lu seconds in future\n",
		       pk->timestamp - get_seconds());

	atomic_inc(&pk->count);

	down_write(&keyring_sem);
	list_add_tail(&pk->link, &keyring);
	up_write(&keyring_sem);

	return 0;
}