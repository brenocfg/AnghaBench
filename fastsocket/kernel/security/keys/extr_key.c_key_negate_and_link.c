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
struct key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOKEY ; 
 int key_reject_and_link (struct key*,unsigned int,int /*<<< orphan*/ ,struct key*,struct key*) ; 

int key_negate_and_link(struct key *key,
			unsigned timeout,
			struct key *keyring,
			struct key *instkey)
{
	return key_reject_and_link(key, timeout, ENOKEY, keyring, instkey);
}