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
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;
struct key {TYPE_1__ payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_free_blkcipher (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rxrpc_destroy_s(struct key *key)
{
	if (key->payload.data) {
		crypto_free_blkcipher(key->payload.data);
		key->payload.data = NULL;
	}
}