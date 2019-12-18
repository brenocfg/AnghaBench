#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct neon_type_el {scalar_t__ type; int /*<<< orphan*/  size; } ;
struct TYPE_4__ {int /*<<< orphan*/  instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {scalar_t__ isscalar; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEON_ENC_INTEGER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEON_ENC_POLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_QDD ; 
 scalar_t__ NT_poly ; 
 int N_DBL ; 
 int N_EQK ; 
 int N_KEY ; 
 int N_P8 ; 
 int N_SU_32 ; 
 int /*<<< orphan*/  do_neon_mac_maybe_scalar_long () ; 
 TYPE_2__ inst ; 
 struct neon_type_el neon_check_type (int,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  neon_mixed_length (struct neon_type_el,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_neon_vmull (void)
{
  if (inst.operands[2].isscalar)
    do_neon_mac_maybe_scalar_long ();
  else
    {
      struct neon_type_el et = neon_check_type (3, NS_QDD,
        N_EQK | N_DBL, N_EQK, N_SU_32 | N_P8 | N_KEY);
      if (et.type == NT_poly)
        inst.instruction = NEON_ENC_POLY (inst.instruction);
      else
        inst.instruction = NEON_ENC_INTEGER (inst.instruction);
      /* For polynomial encoding, size field must be 0b00 and the U bit must be
         zero. Should be OK as-is.  */
      neon_mixed_length (et, et.size);
    }
}