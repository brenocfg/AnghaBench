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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
#define  EQ 131 
#define  GE 130 
#define  GT 129 
#define  GTU 128 
 int INSN_NOT_AVAILABLE ; 
 int /*<<< orphan*/  TARGET_ALTIVEC ; 
 int UNSPEC_VCMPEQFP ; 
 int UNSPEC_VCMPEQUB ; 
 int UNSPEC_VCMPEQUH ; 
 int UNSPEC_VCMPEQUW ; 
 int UNSPEC_VCMPGEFP ; 
 int UNSPEC_VCMPGTFP ; 
 int UNSPEC_VCMPGTSB ; 
 int UNSPEC_VCMPGTSH ; 
 int UNSPEC_VCMPGTSW ; 
 int UNSPEC_VCMPGTUB ; 
 int UNSPEC_VCMPGTUH ; 
 int UNSPEC_VCMPGTUW ; 
 int V16QImode ; 
 int V4SFmode ; 
 int V4SImode ; 
 int V8HImode ; 

__attribute__((used)) static int
get_vec_cmp_insn (enum rtx_code code,
		  enum machine_mode dest_mode,
		  enum machine_mode op_mode)
{
  if (!TARGET_ALTIVEC)
    return INSN_NOT_AVAILABLE;

  switch (code)
    {
    case EQ:
      if (dest_mode == V16QImode && op_mode == V16QImode)
	return UNSPEC_VCMPEQUB;
      if (dest_mode == V8HImode && op_mode == V8HImode)
	return UNSPEC_VCMPEQUH;
      if (dest_mode == V4SImode && op_mode == V4SImode)
	return UNSPEC_VCMPEQUW;
      if (dest_mode == V4SImode && op_mode == V4SFmode)
	return UNSPEC_VCMPEQFP;
      break;
    case GE:
      if (dest_mode == V4SImode && op_mode == V4SFmode)
	return UNSPEC_VCMPGEFP;
    case GT:
      if (dest_mode == V16QImode && op_mode == V16QImode)
	return UNSPEC_VCMPGTSB;
      if (dest_mode == V8HImode && op_mode == V8HImode)
	return UNSPEC_VCMPGTSH;
      if (dest_mode == V4SImode && op_mode == V4SImode)
	return UNSPEC_VCMPGTSW;
      if (dest_mode == V4SImode && op_mode == V4SFmode)
	return UNSPEC_VCMPGTFP;
      break;
    case GTU:
      if (dest_mode == V16QImode && op_mode == V16QImode)
	return UNSPEC_VCMPGTUB;
      if (dest_mode == V8HImode && op_mode == V8HImode)
	return UNSPEC_VCMPGTUH;
      if (dest_mode == V4SImode && op_mode == V4SImode)
	return UNSPEC_VCMPGTUW;
      break;
    default:
      break;
    }
  return INSN_NOT_AVAILABLE;
}