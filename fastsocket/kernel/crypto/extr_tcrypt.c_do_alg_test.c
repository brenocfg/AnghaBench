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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_ALG_TYPE_MASK ; 
 int ENOENT ; 
 scalar_t__ crypto_has_alg (char const*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_alg_test(const char *alg, u32 type, u32 mask)
{
	return crypto_has_alg(alg, type, mask ?: CRYPTO_ALG_TYPE_MASK) ?
	       0 : -ENOENT;
}