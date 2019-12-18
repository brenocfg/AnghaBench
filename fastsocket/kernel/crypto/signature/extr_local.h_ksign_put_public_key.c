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
struct ksign_public_key {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksign_free_public_key (struct ksign_public_key*) ; 

__attribute__((used)) static inline void ksign_put_public_key(struct ksign_public_key *pk)
{
	if (atomic_dec_and_test(&pk->count))
		ksign_free_public_key(pk);
}