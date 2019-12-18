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

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_S390_MSA ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  KIMD_SHA_256 ; 
 int /*<<< orphan*/  alg ; 
 int /*<<< orphan*/  crypt_s390_func_available (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int crypto_register_shash (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sha256_s390_init(void)
{
	if (!crypt_s390_func_available(KIMD_SHA_256, CRYPT_S390_MSA))
		return -EOPNOTSUPP;

	return crypto_register_shash(&alg);
}