#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* mul ) (unsigned char*,size_t,unsigned char const*,size_t,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  (* mul ) (unsigned char*,size_t,unsigned char const*,size_t,int) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* mul ) (unsigned char*,size_t,unsigned char const*,size_t,int) ;} ;

/* Variables and functions */
#define  BR_EC_curve25519 129 
#define  BR_EC_secp256r1 128 
 TYPE_3__ br_ec_c25519_m15 ; 
 TYPE_2__ br_ec_p256_m15 ; 
 TYPE_1__ br_ec_prime_i15 ; 
 int /*<<< orphan*/  stub1 (unsigned char*,size_t,unsigned char const*,size_t,int) ; 
 int /*<<< orphan*/  stub2 (unsigned char*,size_t,unsigned char const*,size_t,int) ; 
 int /*<<< orphan*/  stub3 (unsigned char*,size_t,unsigned char const*,size_t,int) ; 

__attribute__((used)) static uint32_t
api_mul(unsigned char *G, size_t Glen,
	const unsigned char *kb, size_t kblen, int curve)
{
	switch (curve) {
	case BR_EC_secp256r1:
		return br_ec_p256_m15.mul(G, Glen, kb, kblen, curve);
	case BR_EC_curve25519:
		return br_ec_c25519_m15.mul(G, Glen, kb, kblen, curve);
	default:
		return br_ec_prime_i15.mul(G, Glen, kb, kblen, curve);
	}
}