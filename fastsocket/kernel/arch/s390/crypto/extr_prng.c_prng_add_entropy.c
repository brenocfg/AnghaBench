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
typedef  int /*<<< orphan*/  entropy ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  KMC_PRNG ; 
 int crypt_s390_kmc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  parm_block ; 

__attribute__((used)) static void prng_add_entropy(void)
{
	__u64 entropy[4];
	unsigned int i;
	int ret;

	for (i = 0; i < 16; i++) {
		ret = crypt_s390_kmc(KMC_PRNG, parm_block, (char *)entropy,
				     (char *)entropy, sizeof(entropy));
		BUG_ON(ret < 0 || ret != sizeof(entropy));
		memcpy(parm_block, entropy, sizeof(entropy));
	}
}