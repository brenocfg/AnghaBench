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
typedef  enum neon_shape { ____Placeholder_neon_shape } neon_shape ;

/* Variables and functions */
 int /*<<< orphan*/  NS_DD ; 
 int NS_FF ; 
 int /*<<< orphan*/  NS_NULL ; 
 int N_EQK ; 
 int N_F32 ; 
 int N_F64 ; 
 int N_KEY ; 
 int N_VFP ; 
 int /*<<< orphan*/  do_vfp_nsyn_opcode (char*) ; 
 int /*<<< orphan*/  neon_check_type (int,int,int,int) ; 
 int neon_select_shape (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_vfp_nsyn_sqrt (void)
{
  enum neon_shape rs = neon_select_shape (NS_FF, NS_DD, NS_NULL);
  neon_check_type (2, rs, N_EQK | N_VFP, N_F32 | N_F64 | N_KEY | N_VFP);
      
  if (rs == NS_FF)
    do_vfp_nsyn_opcode ("fsqrts");
  else
    do_vfp_nsyn_opcode ("fsqrtd");
}