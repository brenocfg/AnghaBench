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
struct TYPE_6__ {size_t (* mulgen ) (unsigned char*,unsigned char const*,size_t,int) ;} ;
struct TYPE_5__ {size_t (* mulgen ) (unsigned char*,unsigned char const*,size_t,int) ;} ;
struct TYPE_4__ {size_t (* mulgen ) (unsigned char*,unsigned char const*,size_t,int) ;} ;

/* Variables and functions */
#define  BR_EC_curve25519 129 
#define  BR_EC_secp256r1 128 
 TYPE_3__ br_ec_c25519_m15 ; 
 TYPE_2__ br_ec_p256_m15 ; 
 TYPE_1__ br_ec_prime_i15 ; 
 size_t stub1 (unsigned char*,unsigned char const*,size_t,int) ; 
 size_t stub2 (unsigned char*,unsigned char const*,size_t,int) ; 
 size_t stub3 (unsigned char*,unsigned char const*,size_t,int) ; 

__attribute__((used)) static size_t
api_mulgen(unsigned char *R,
	const unsigned char *x, size_t xlen, int curve)
{
	switch (curve) {
	case BR_EC_secp256r1:
		return br_ec_p256_m15.mulgen(R, x, xlen, curve);
	case BR_EC_curve25519:
		return br_ec_c25519_m15.mulgen(R, x, xlen, curve);
	default:
		return br_ec_prime_i15.mulgen(R, x, xlen, curve);
	}
}