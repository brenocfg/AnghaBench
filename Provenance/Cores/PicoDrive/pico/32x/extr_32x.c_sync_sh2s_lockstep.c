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
struct TYPE_4__ {unsigned int m68krcycles_done; } ;
struct TYPE_3__ {unsigned int m68krcycles_done; } ;

/* Variables and functions */
 scalar_t__ STEP_68K ; 
 TYPE_2__ msh2 ; 
 TYPE_1__ ssh2 ; 
 int /*<<< orphan*/  sync_sh2s_normal (unsigned int) ; 

void sync_sh2s_lockstep(unsigned int m68k_target)
{
  unsigned int mcycles;
  
  mcycles = msh2.m68krcycles_done;
  if (ssh2.m68krcycles_done < mcycles)
    mcycles = ssh2.m68krcycles_done;

  while (mcycles < m68k_target) {
    mcycles += STEP_68K;
    sync_sh2s_normal(mcycles);
  }
}