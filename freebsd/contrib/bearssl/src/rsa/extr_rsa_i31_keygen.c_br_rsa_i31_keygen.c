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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  br_rsa_public_key ;
typedef  int /*<<< orphan*/  br_rsa_private_key ;
typedef  int /*<<< orphan*/  br_prng_class ;

/* Variables and functions */
 int /*<<< orphan*/  br_i31_modpow_opt ; 
 int /*<<< orphan*/  br_rsa_i31_keygen_inner (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,void*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

uint32_t
br_rsa_i31_keygen(const br_prng_class **rng,
	br_rsa_private_key *sk, void *kbuf_priv,
	br_rsa_public_key *pk, void *kbuf_pub,
	unsigned size, uint32_t pubexp)
{
	return br_rsa_i31_keygen_inner(rng,
		sk, kbuf_priv, pk, kbuf_pub, size, pubexp,
		&br_i31_modpow_opt);
}