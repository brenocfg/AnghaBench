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
typedef  enum neon_shape { ____Placeholder_neon_shape } neon_shape ;
struct TYPE_2__ {int instruction; } ;

/* Variables and functions */
 int NS_FF ; 
 int N_EQK ; 
 int N_F32 ; 
 int N_F64 ; 
 int N_KEY ; 
 int N_VFP ; 
 int /*<<< orphan*/  do_vfp_nsyn_opcode (char*) ; 
 TYPE_1__ inst ; 
 int /*<<< orphan*/  neon_check_type (int,int,int,int) ; 

__attribute__((used)) static void
do_vfp_nsyn_abs_neg (enum neon_shape rs)
{
  int is_neg = (inst.instruction & 0x80) != 0;
  neon_check_type (2, rs, N_EQK | N_VFP, N_F32 | N_F64 | N_VFP | N_KEY);

  if (rs == NS_FF)
    {
      if (is_neg)
        do_vfp_nsyn_opcode ("fnegs");
      else
        do_vfp_nsyn_opcode ("fabss");
    }
  else
    {
      if (is_neg)
        do_vfp_nsyn_opcode ("fnegd");
      else
        do_vfp_nsyn_opcode ("fabsd");
    }
}