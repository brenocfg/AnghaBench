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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_VECTOR_ELT (int /*<<< orphan*/ ,int) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE_NUNITS (int) ; 
 int /*<<< orphan*/  HImode ; 
 int /*<<< orphan*/  QImode ; 
 int /*<<< orphan*/  SImode ; 
 int /*<<< orphan*/  V16QImode ; 
 int /*<<< orphan*/  V4SImode ; 
 int /*<<< orphan*/  V8HImode ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_lowpart (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_VEC_DUPLICATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vspltis_constant (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

rtx
gen_easy_altivec_constant (rtx op)
{
  enum machine_mode mode = GET_MODE (op);
  int nunits = GET_MODE_NUNITS (mode);
  rtx last = CONST_VECTOR_ELT (op, nunits - 1);
  unsigned step = nunits / 4;
  unsigned copies = 1;

  /* Start with a vspltisw.  */
  if (vspltis_constant (op, step, copies))
    return gen_rtx_VEC_DUPLICATE (V4SImode, gen_lowpart (SImode, last));

  /* Then try with a vspltish.  */
  if (step == 1)
    copies <<= 1;
  else
    step >>= 1;

  if (vspltis_constant (op, step, copies))
    return gen_rtx_VEC_DUPLICATE (V8HImode, gen_lowpart (HImode, last));

  /* And finally a vspltisb.  */
  if (step == 1)
    copies <<= 1;
  else
    step >>= 1;

  if (vspltis_constant (op, step, copies))
    return gen_rtx_VEC_DUPLICATE (V16QImode, gen_lowpart (QImode, last));

  gcc_unreachable ();
}