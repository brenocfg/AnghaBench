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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  br_i62_modpow_opt (int /*<<< orphan*/ *,unsigned char const*,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

uint32_t
br_i62_modpow_opt_as_i31(uint32_t *x31, const unsigned char *e, size_t elen,
	const uint32_t *m31, uint32_t m0i31, uint32_t *tmp, size_t twlen)
{
	/*
	 * As documented, this function expects the 'tmp' argument to be
	 * 64-bit aligned. This is OK since this function is internal (it
	 * is not part of BearSSL's public API).
	 */
	return br_i62_modpow_opt(x31, e, elen, m31, m0i31,
		(uint64_t *)tmp, twlen >> 1);
}