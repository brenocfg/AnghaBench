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
typedef  int /*<<< orphan*/  u32 ;
struct vfp_single {int exponent; int /*<<< orphan*/  significand; int /*<<< orphan*/  sign; } ;
struct vfp_double {int exponent; int /*<<< orphan*/  significand; int /*<<< orphan*/  sign; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPSCR_IOC ; 
 int VFP_DENORMAL ; 
 int VFP_INFINITY ; 
 int VFP_NAN ; 
 int VFP_QNAN ; 
 int /*<<< orphan*/  VFP_SINGLE_SIGNIFICAND_QNAN ; 
 int VFP_SNAN ; 
 int VFP_ZERO ; 
 int /*<<< orphan*/  vfp_double_normalise_denormal (struct vfp_double*) ; 
 int vfp_double_type (struct vfp_double*) ; 
 int /*<<< orphan*/  vfp_double_unpack (struct vfp_double*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfp_get_double (int) ; 
 int /*<<< orphan*/  vfp_hi64to32jamming (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfp_put_float (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfp_single_normaliseround (int,struct vfp_single*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vfp_single_pack (struct vfp_single*) ; 

__attribute__((used)) static u32 vfp_double_fcvts(int sd, int unused, int dm, u32 fpscr)
{
	struct vfp_double vdm;
	struct vfp_single vsd;
	int tm;
	u32 exceptions = 0;

	vfp_double_unpack(&vdm, vfp_get_double(dm));

	tm = vfp_double_type(&vdm);

	/*
	 * If we have a signalling NaN, signal invalid operation.
	 */
	if (tm == VFP_SNAN)
		exceptions = FPSCR_IOC;

	if (tm & VFP_DENORMAL)
		vfp_double_normalise_denormal(&vdm);

	vsd.sign = vdm.sign;
	vsd.significand = vfp_hi64to32jamming(vdm.significand);

	/*
	 * If we have an infinity or a NaN, the exponent must be 255
	 */
	if (tm & (VFP_INFINITY|VFP_NAN)) {
		vsd.exponent = 255;
		if (tm == VFP_QNAN)
			vsd.significand |= VFP_SINGLE_SIGNIFICAND_QNAN;
		goto pack_nan;
	} else if (tm & VFP_ZERO)
		vsd.exponent = 0;
	else
		vsd.exponent = vdm.exponent - (1023 - 127);

	return vfp_single_normaliseround(sd, &vsd, fpscr, exceptions, "fcvts");

 pack_nan:
	vfp_put_float(vfp_single_pack(&vsd), sd);
	return exceptions;
}