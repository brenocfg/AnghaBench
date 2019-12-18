#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct neon_type_el {scalar_t__ type; int size; } ;
struct TYPE_2__ {int instruction; } ;

/* Variables and functions */
 int NEON_ENC_INTEGER (int) ; 
 int /*<<< orphan*/  NS_DQ ; 
 scalar_t__ NT_unsigned ; 
 int N_EQK ; 
 int N_HLF ; 
 int N_KEY ; 
 int N_SU_16_64 ; 
 TYPE_1__ inst ; 
 struct neon_type_el neon_check_type (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  neon_two_same (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
do_neon_qmovn (void)
{
  struct neon_type_el et = neon_check_type (2, NS_DQ,
    N_EQK | N_HLF, N_SU_16_64 | N_KEY);
  /* Saturating move where operands can be signed or unsigned, and the
     destination has the same signedness.  */
  inst.instruction = NEON_ENC_INTEGER (inst.instruction);
  if (et.type == NT_unsigned)
    inst.instruction |= 0xc0;
  else
    inst.instruction |= 0x80;
  neon_two_same (0, 1, et.size / 2);
}