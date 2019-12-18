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
struct neon_type_el {int size; } ;
struct TYPE_2__ {int /*<<< orphan*/  instruction; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEON_ENC_INTEGER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NS_DQ ; 
 int N_EQK ; 
 int N_HLF ; 
 int N_KEY ; 
 int N_S16 ; 
 int N_S32 ; 
 int N_S64 ; 
 int N_UNS ; 
 TYPE_1__ inst ; 
 struct neon_type_el neon_check_type (int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  neon_two_same (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
do_neon_qmovun (void)
{
  struct neon_type_el et = neon_check_type (2, NS_DQ,
    N_EQK | N_HLF | N_UNS, N_S16 | N_S32 | N_S64 | N_KEY);
  /* Saturating move with unsigned results. Operands must be signed.  */
  inst.instruction = NEON_ENC_INTEGER (inst.instruction);
  neon_two_same (0, 1, et.size / 2);
}