#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {unsigned char const* (* generator ) (int,size_t*) ;} ;
struct TYPE_9__ {unsigned char const* (* generator ) (int,size_t*) ;} ;
struct TYPE_8__ {unsigned char const* (* generator ) (int,size_t*) ;} ;
struct TYPE_7__ {unsigned char const* (* generator ) (int,size_t*) ;} ;
struct TYPE_6__ {unsigned char const* (* generator ) (int,size_t*) ;} ;

/* Variables and functions */
#define  BR_EC_curve25519 129 
#define  BR_EC_secp256r1 128 
 TYPE_5__ br_ec_c25519_m31 ; 
 TYPE_4__ br_ec_c25519_m64 ; 
 TYPE_3__ br_ec_p256_m31 ; 
 TYPE_2__ br_ec_p256_m64 ; 
 TYPE_1__ br_ec_prime_i31 ; 
 unsigned char const* stub1 (int,size_t*) ; 
 unsigned char const* stub2 (int,size_t*) ; 
 unsigned char const* stub3 (int,size_t*) ; 
 unsigned char const* stub4 (int,size_t*) ; 
 unsigned char const* stub5 (int,size_t*) ; 

__attribute__((used)) static const unsigned char *
api_generator(int curve, size_t *len)
{
	switch (curve) {
	case BR_EC_secp256r1:
#if BR_INT128 || BR_UMUL128
		return br_ec_p256_m64.generator(curve, len);
#else
		return br_ec_p256_m31.generator(curve, len);
#endif
	case BR_EC_curve25519:
#if BR_INT128 || BR_UMUL128
		return br_ec_c25519_m64.generator(curve, len);
#else
		return br_ec_c25519_m31.generator(curve, len);
#endif
	default:
		return br_ec_prime_i31.generator(curve, len);
	}
}