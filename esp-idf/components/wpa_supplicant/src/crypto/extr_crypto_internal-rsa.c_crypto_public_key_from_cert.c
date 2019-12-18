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
typedef  int /*<<< orphan*/  u8 ;
struct crypto_public_key {int dummy; } ;

/* Variables and functions */

struct crypto_public_key *  crypto_public_key_from_cert(const u8 *buf,
						       size_t len)
{
	/* No X.509 support in crypto_internal.c */
	return NULL;
}