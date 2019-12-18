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

/* Variables and functions */
 scalar_t__ BYTES_BIG_ENDIAN ; 
 scalar_t__ DFmode ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SImode ; 
 scalar_t__ SPE_VECTOR_MODE (scalar_t__) ; 
 scalar_t__ TARGET_E500_DOUBLE ; 
 scalar_t__ TARGET_SPE ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  gen_rtvec (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_PARALLEL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_REG (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static rtx
rs6000_dwarf_register_span (rtx reg)
{
  unsigned regno;

  if (TARGET_SPE
      && (SPE_VECTOR_MODE (GET_MODE (reg))
	  || (TARGET_E500_DOUBLE && GET_MODE (reg) == DFmode)))
    ;
  else
    return NULL_RTX;

  regno = REGNO (reg);

  /* The duality of the SPE register size wreaks all kinds of havoc.
     This is a way of distinguishing r0 in 32-bits from r0 in
     64-bits.  */
  return
    gen_rtx_PARALLEL (VOIDmode,
		      BYTES_BIG_ENDIAN
		      ? gen_rtvec (2,
				   gen_rtx_REG (SImode, regno + 1200),
				   gen_rtx_REG (SImode, regno))
		      : gen_rtvec (2,
				   gen_rtx_REG (SImode, regno),
				   gen_rtx_REG (SImode, regno + 1200)));
}