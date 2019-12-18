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
 int NS_FFF ; 
 int N_MNEM_vmla ; 
 int /*<<< orphan*/  do_vfp_nsyn_opcode (char*) ; 
 TYPE_1__ inst ; 

__attribute__((used)) static void
do_vfp_nsyn_mla_mls (enum neon_shape rs)
{
  int is_mla = (inst.instruction & 0x0fffffff) == N_MNEM_vmla;
  
  if (rs == NS_FFF)
    {
      if (is_mla)
        do_vfp_nsyn_opcode ("fmacs");
      else
        do_vfp_nsyn_opcode ("fmscs");
    }
  else
    {
      if (is_mla)
        do_vfp_nsyn_opcode ("fmacd");
      else
        do_vfp_nsyn_opcode ("fmscd");
    }
}