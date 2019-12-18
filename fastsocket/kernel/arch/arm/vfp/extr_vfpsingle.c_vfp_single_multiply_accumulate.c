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
typedef  int u32 ;
struct vfp_single {scalar_t__ exponent; void* sign; scalar_t__ significand; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int NEG_MULTIPLY ; 
 int NEG_SUBTRACT ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfp_get_float (int) ; 
 void* vfp_sign_negate (void*) ; 
 int vfp_single_add (struct vfp_single*,struct vfp_single*,struct vfp_single*,int) ; 
 int vfp_single_multiply (struct vfp_single*,struct vfp_single*,struct vfp_single*,int) ; 
 int /*<<< orphan*/  vfp_single_normalise_denormal (struct vfp_single*) ; 
 int vfp_single_normaliseround (int,struct vfp_single*,int,int,char*) ; 
 int /*<<< orphan*/  vfp_single_unpack (struct vfp_single*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
vfp_single_multiply_accumulate(int sd, int sn, s32 m, u32 fpscr, u32 negate, char *func)
{
	struct vfp_single vsd, vsp, vsn, vsm;
	u32 exceptions;
	s32 v;

	v = vfp_get_float(sn);
	pr_debug("VFP: s%u = %08x\n", sn, v);
	vfp_single_unpack(&vsn, v);
	if (vsn.exponent == 0 && vsn.significand)
		vfp_single_normalise_denormal(&vsn);

	vfp_single_unpack(&vsm, m);
	if (vsm.exponent == 0 && vsm.significand)
		vfp_single_normalise_denormal(&vsm);

	exceptions = vfp_single_multiply(&vsp, &vsn, &vsm, fpscr);
	if (negate & NEG_MULTIPLY)
		vsp.sign = vfp_sign_negate(vsp.sign);

	v = vfp_get_float(sd);
	pr_debug("VFP: s%u = %08x\n", sd, v);
	vfp_single_unpack(&vsn, v);
	if (negate & NEG_SUBTRACT)
		vsn.sign = vfp_sign_negate(vsn.sign);

	exceptions |= vfp_single_add(&vsd, &vsn, &vsp, fpscr);

	return vfp_single_normaliseround(sd, &vsd, fpscr, exceptions, func);
}