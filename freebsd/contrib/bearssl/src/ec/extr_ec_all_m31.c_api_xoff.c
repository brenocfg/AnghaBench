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
struct TYPE_10__ {size_t (* xoff ) (int,size_t*) ;} ;
struct TYPE_9__ {size_t (* xoff ) (int,size_t*) ;} ;
struct TYPE_8__ {size_t (* xoff ) (int,size_t*) ;} ;
struct TYPE_7__ {size_t (* xoff ) (int,size_t*) ;} ;
struct TYPE_6__ {size_t (* xoff ) (int,size_t*) ;} ;

/* Variables and functions */
#define  BR_EC_curve25519 129 
#define  BR_EC_secp256r1 128 
 TYPE_5__ br_ec_c25519_m31 ; 
 TYPE_4__ br_ec_c25519_m64 ; 
 TYPE_3__ br_ec_p256_m31 ; 
 TYPE_2__ br_ec_p256_m64 ; 
 TYPE_1__ br_ec_prime_i31 ; 
 size_t stub1 (int,size_t*) ; 
 size_t stub2 (int,size_t*) ; 
 size_t stub3 (int,size_t*) ; 
 size_t stub4 (int,size_t*) ; 
 size_t stub5 (int,size_t*) ; 

__attribute__((used)) static size_t
api_xoff(int curve, size_t *len)
{
	switch (curve) {
	case BR_EC_secp256r1:
#if BR_INT128 || BR_UMUL128
		return br_ec_p256_m64.xoff(curve, len);
#else
		return br_ec_p256_m31.xoff(curve, len);
#endif
	case BR_EC_curve25519:
#if BR_INT128 || BR_UMUL128
		return br_ec_c25519_m64.xoff(curve, len);
#else
		return br_ec_c25519_m31.xoff(curve, len);
#endif
	default:
		return br_ec_prime_i31.xoff(curve, len);
	}
}