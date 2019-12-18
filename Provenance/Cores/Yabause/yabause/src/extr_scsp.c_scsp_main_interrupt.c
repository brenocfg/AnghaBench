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
typedef  int u32 ;
struct TYPE_2__ {int mcipd; int mcieb; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_THROUGH (int) ; 
 TYPE_1__ scsp ; 
 int /*<<< orphan*/  scsp_trigger_main_interrupt (int) ; 

__attribute__((used)) static void
scsp_main_interrupt (u32 id)
{
//  if (scsp.mcipd & id) return;
//  if (id != 0x400) SCSPLOG("scsp main interrupt %.4X\n", id);

  scsp.mcipd |= id;
  WRITE_THROUGH (scsp.mcipd);

  if (scsp.mcieb & id)
    scsp_trigger_main_interrupt (id);
}