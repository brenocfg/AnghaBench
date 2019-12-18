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
struct TYPE_3__ {scalar_t__ frame_count; } ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 int /*<<< orphan*/  CycloneInitIdle () ; 
 TYPE_2__ Pico ; 
 int /*<<< orphan*/  fm68k_emulate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (unsigned short**) ; 
 scalar_t__ idledet_bads ; 
 scalar_t__ idledet_count ; 
 unsigned short** idledet_ptrs ; 
 scalar_t__ idledet_start_frame ; 
 scalar_t__* idlehit_addrs ; 
 unsigned short** realloc (unsigned short**,int) ; 

void SekInitIdleDet(void)
{
  unsigned short **tmp = realloc(idledet_ptrs, 0x200*4);
  if (tmp == NULL) {
    free(idledet_ptrs);
    idledet_ptrs = NULL;
  }
  else
    idledet_ptrs = tmp;
  idledet_count = idledet_bads = 0;
  idledet_start_frame = Pico.m.frame_count + 360;
#ifdef IDLE_STATS
  idlehit_addrs[0] = 0;
#endif

#ifdef EMU_C68K
  CycloneInitIdle();
#endif
#ifdef EMU_F68K
  fm68k_emulate(0, 1);
#endif
}