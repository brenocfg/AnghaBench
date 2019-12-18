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
struct ia64_frame_cache {int /*<<< orphan*/  base; void** saved_regs; } ;

/* Variables and functions */
 int IA64_BR0_REGNUM ; 
 int IA64_BR7_REGNUM ; 
 size_t IA64_BSP_REGNUM ; 
 size_t IA64_CCV_REGNUM ; 
 size_t IA64_CFM_REGNUM ; 
 size_t IA64_FPSR_REGNUM ; 
 int IA64_FR2_REGNUM ; 
 int IA64_FR31_REGNUM ; 
 int IA64_GR1_REGNUM ; 
 int IA64_GR31_REGNUM ; 
 int IA64_IP_REGNUM ; 
 size_t IA64_LC_REGNUM ; 
 size_t IA64_PFS_REGNUM ; 
 size_t IA64_PSR_REGNUM ; 
 size_t IA64_RNAT_REGNUM ; 
 size_t IA64_UNAT_REGNUM ; 
 size_t IA64_VRAP_REGNUM ; 
 void* SIGCONTEXT_REGISTER_ADDRESS (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ia64_sigtramp_frame_init_saved_regs (struct ia64_frame_cache *cache)
{
  if (SIGCONTEXT_REGISTER_ADDRESS)
    {
      int regno;

      cache->saved_regs[IA64_VRAP_REGNUM] = 
	SIGCONTEXT_REGISTER_ADDRESS (cache->base, IA64_IP_REGNUM);
      cache->saved_regs[IA64_CFM_REGNUM] = 
	SIGCONTEXT_REGISTER_ADDRESS (cache->base, IA64_CFM_REGNUM);
      cache->saved_regs[IA64_PSR_REGNUM] = 
	SIGCONTEXT_REGISTER_ADDRESS (cache->base, IA64_PSR_REGNUM);
      cache->saved_regs[IA64_BSP_REGNUM] = 
	SIGCONTEXT_REGISTER_ADDRESS (cache->base, IA64_BSP_REGNUM);
      cache->saved_regs[IA64_RNAT_REGNUM] = 
	SIGCONTEXT_REGISTER_ADDRESS (cache->base, IA64_RNAT_REGNUM);
      cache->saved_regs[IA64_CCV_REGNUM] = 
	SIGCONTEXT_REGISTER_ADDRESS (cache->base, IA64_CCV_REGNUM);
      cache->saved_regs[IA64_UNAT_REGNUM] = 
	SIGCONTEXT_REGISTER_ADDRESS (cache->base, IA64_UNAT_REGNUM);
      cache->saved_regs[IA64_FPSR_REGNUM] = 
	SIGCONTEXT_REGISTER_ADDRESS (cache->base, IA64_FPSR_REGNUM);
      cache->saved_regs[IA64_PFS_REGNUM] = 
	SIGCONTEXT_REGISTER_ADDRESS (cache->base, IA64_PFS_REGNUM);
      cache->saved_regs[IA64_LC_REGNUM] = 
	SIGCONTEXT_REGISTER_ADDRESS (cache->base, IA64_LC_REGNUM);
      for (regno = IA64_GR1_REGNUM; regno <= IA64_GR31_REGNUM; regno++)
	cache->saved_regs[regno] =
	  SIGCONTEXT_REGISTER_ADDRESS (cache->base, regno);
      for (regno = IA64_BR0_REGNUM; regno <= IA64_BR7_REGNUM; regno++)
	cache->saved_regs[regno] =
	  SIGCONTEXT_REGISTER_ADDRESS (cache->base, regno);
      for (regno = IA64_FR2_REGNUM; regno <= IA64_FR31_REGNUM; regno++)
	cache->saved_regs[regno] =
	  SIGCONTEXT_REGISTER_ADDRESS (cache->base, regno);
    }
}