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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_10__ {int /*<<< orphan*/  (* muladd ) (unsigned char*,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char const*,size_t,int) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  (* muladd ) (unsigned char*,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char const*,size_t,int) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  (* muladd ) (unsigned char*,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char const*,size_t,int) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  (* muladd ) (unsigned char*,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char const*,size_t,int) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* muladd ) (unsigned char*,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char const*,size_t,int) ;} ;

/* Variables and functions */
#define  BR_EC_curve25519 129 
#define  BR_EC_secp256r1 128 
 TYPE_5__ br_ec_c25519_m31 ; 
 TYPE_4__ br_ec_c25519_m64 ; 
 TYPE_3__ br_ec_p256_m31 ; 
 TYPE_2__ br_ec_p256_m64 ; 
 TYPE_1__ br_ec_prime_i31 ; 
 int /*<<< orphan*/  stub1 (unsigned char*,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char const*,size_t,int) ; 
 int /*<<< orphan*/  stub2 (unsigned char*,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char const*,size_t,int) ; 
 int /*<<< orphan*/  stub3 (unsigned char*,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char const*,size_t,int) ; 
 int /*<<< orphan*/  stub4 (unsigned char*,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char const*,size_t,int) ; 
 int /*<<< orphan*/  stub5 (unsigned char*,unsigned char const*,size_t,unsigned char const*,size_t,unsigned char const*,size_t,int) ; 

__attribute__((used)) static uint32_t
api_muladd(unsigned char *A, const unsigned char *B, size_t len,
	const unsigned char *x, size_t xlen,
	const unsigned char *y, size_t ylen, int curve)
{
	switch (curve) {
	case BR_EC_secp256r1:
#if BR_INT128 || BR_UMUL128
		return br_ec_p256_m64.muladd(A, B, len,
			x, xlen, y, ylen, curve);
#else
		return br_ec_p256_m31.muladd(A, B, len,
			x, xlen, y, ylen, curve);
#endif
	case BR_EC_curve25519:
#if BR_INT128 || BR_UMUL128
		return br_ec_c25519_m64.muladd(A, B, len,
			x, xlen, y, ylen, curve);
#else
		return br_ec_c25519_m31.muladd(A, B, len,
			x, xlen, y, ylen, curve);
#endif
	default:
		return br_ec_prime_i31.muladd(A, B, len,
			x, xlen, y, ylen, curve);
	}
}