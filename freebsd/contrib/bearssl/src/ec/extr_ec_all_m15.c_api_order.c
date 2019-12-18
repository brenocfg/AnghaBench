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
struct TYPE_6__ {unsigned char const* (* order ) (int,size_t*) ;} ;
struct TYPE_5__ {unsigned char const* (* order ) (int,size_t*) ;} ;
struct TYPE_4__ {unsigned char const* (* order ) (int,size_t*) ;} ;

/* Variables and functions */
#define  BR_EC_curve25519 129 
#define  BR_EC_secp256r1 128 
 TYPE_3__ br_ec_c25519_m15 ; 
 TYPE_2__ br_ec_p256_m15 ; 
 TYPE_1__ br_ec_prime_i15 ; 
 unsigned char const* stub1 (int,size_t*) ; 
 unsigned char const* stub2 (int,size_t*) ; 
 unsigned char const* stub3 (int,size_t*) ; 

__attribute__((used)) static const unsigned char *
api_order(int curve, size_t *len)
{
	switch (curve) {
	case BR_EC_secp256r1:
		return br_ec_p256_m15.order(curve, len);
	case BR_EC_curve25519:
		return br_ec_c25519_m15.order(curve, len);
	default:
		return br_ec_prime_i15.order(curve, len);
	}
}