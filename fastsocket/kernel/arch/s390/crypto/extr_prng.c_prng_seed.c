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
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  get_random_bytes (char*,int) ; 
 scalar_t__ parm_block ; 
 int /*<<< orphan*/  prng_add_entropy () ; 

__attribute__((used)) static void prng_seed(int nbytes)
{
	char buf[16];
	int i = 0;

	BUG_ON(nbytes > 16);
	get_random_bytes(buf, nbytes);

	/* Add the entropy */
	while (nbytes >= 8) {
		*((__u64 *)parm_block) ^= *((__u64 *)(buf+i));
		prng_add_entropy();
		i += 8;
		nbytes -= 8;
	}
	prng_add_entropy();
}