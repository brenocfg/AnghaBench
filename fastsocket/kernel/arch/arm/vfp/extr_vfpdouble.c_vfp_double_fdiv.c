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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct vfp_double {int sign; int exponent; int significand; } ;
typedef  scalar_t__ s64 ;

/* Variables and functions */
 int /*<<< orphan*/  FPSCR_DZC ; 
 int /*<<< orphan*/  FPSCR_IOC ; 
 int VFP_DENORMAL ; 
 int VFP_INFINITY ; 
 int VFP_NAN ; 
 int VFP_ZERO ; 
 int /*<<< orphan*/  add128 (scalar_t__*,scalar_t__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mul64to128 (scalar_t__*,scalar_t__*,int,int) ; 
 int /*<<< orphan*/  sub128 (scalar_t__*,scalar_t__*,int,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 struct vfp_double vfp_double_default_qnan ; 
 int /*<<< orphan*/  vfp_double_normalise_denormal (struct vfp_double*) ; 
 int /*<<< orphan*/  vfp_double_normaliseround (int,struct vfp_double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vfp_double_pack (struct vfp_double*) ; 
 int vfp_double_type (struct vfp_double*) ; 
 int /*<<< orphan*/  vfp_double_unpack (struct vfp_double*,int /*<<< orphan*/ ) ; 
 int vfp_estimate_div128to64 (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfp_get_double (int) ; 
 int /*<<< orphan*/  vfp_propagate_nan (struct vfp_double*,struct vfp_double*,struct vfp_double*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfp_put_double (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 vfp_double_fdiv(int dd, int dn, int dm, u32 fpscr)
{
	struct vfp_double vdd, vdn, vdm;
	u32 exceptions = 0;
	int tm, tn;

	vfp_double_unpack(&vdn, vfp_get_double(dn));
	vfp_double_unpack(&vdm, vfp_get_double(dm));

	vdd.sign = vdn.sign ^ vdm.sign;

	tn = vfp_double_type(&vdn);
	tm = vfp_double_type(&vdm);

	/*
	 * Is n a NAN?
	 */
	if (tn & VFP_NAN)
		goto vdn_nan;

	/*
	 * Is m a NAN?
	 */
	if (tm & VFP_NAN)
		goto vdm_nan;

	/*
	 * If n and m are infinity, the result is invalid
	 * If n and m are zero, the result is invalid
	 */
	if (tm & tn & (VFP_INFINITY|VFP_ZERO))
		goto invalid;

	/*
	 * If n is infinity, the result is infinity
	 */
	if (tn & VFP_INFINITY)
		goto infinity;

	/*
	 * If m is zero, raise div0 exceptions
	 */
	if (tm & VFP_ZERO)
		goto divzero;

	/*
	 * If m is infinity, or n is zero, the result is zero
	 */
	if (tm & VFP_INFINITY || tn & VFP_ZERO)
		goto zero;

	if (tn & VFP_DENORMAL)
		vfp_double_normalise_denormal(&vdn);
	if (tm & VFP_DENORMAL)
		vfp_double_normalise_denormal(&vdm);

	/*
	 * Ok, we have two numbers, we can perform division.
	 */
	vdd.exponent = vdn.exponent - vdm.exponent + 1023 - 1;
	vdm.significand <<= 1;
	if (vdm.significand <= (2 * vdn.significand)) {
		vdn.significand >>= 1;
		vdd.exponent++;
	}
	vdd.significand = vfp_estimate_div128to64(vdn.significand, 0, vdm.significand);
	if ((vdd.significand & 0x1ff) <= 2) {
		u64 termh, terml, remh, reml;
		mul64to128(&termh, &terml, vdm.significand, vdd.significand);
		sub128(&remh, &reml, vdn.significand, 0, termh, terml);
		while ((s64)remh < 0) {
			vdd.significand -= 1;
			add128(&remh, &reml, remh, reml, 0, vdm.significand);
		}
		vdd.significand |= (reml != 0);
	}
	return vfp_double_normaliseround(dd, &vdd, fpscr, 0, "fdiv");

 vdn_nan:
	exceptions = vfp_propagate_nan(&vdd, &vdn, &vdm, fpscr);
 pack:
	vfp_put_double(vfp_double_pack(&vdd), dd);
	return exceptions;

 vdm_nan:
	exceptions = vfp_propagate_nan(&vdd, &vdm, &vdn, fpscr);
	goto pack;

 zero:
	vdd.exponent = 0;
	vdd.significand = 0;
	goto pack;

 divzero:
	exceptions = FPSCR_DZC;
 infinity:
	vdd.exponent = 2047;
	vdd.significand = 0;
	goto pack;

 invalid:
	vfp_put_double(vfp_double_pack(&vfp_double_default_qnan), dd);
	return FPSCR_IOC;
}