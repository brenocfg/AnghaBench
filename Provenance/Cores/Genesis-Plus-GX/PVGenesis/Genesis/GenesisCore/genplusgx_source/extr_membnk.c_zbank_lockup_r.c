#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* d; } ;
struct TYPE_6__ {int cycles; TYPE_1__ pc; } ;
struct TYPE_5__ {int /*<<< orphan*/  force_dtack; } ;

/* Variables and functions */
 TYPE_3__ Z80 ; 
 TYPE_2__ config ; 
 int /*<<< orphan*/  error (char*,unsigned int,char*) ; 
 scalar_t__ zstate ; 

unsigned int zbank_lockup_r(unsigned int address)
{
#ifdef LOGERROR
  error("Z80 bank lockup read %06X (%x)\n", address, Z80.pc.d);
#endif
  if (!config.force_dtack)
  {
    Z80.cycles = 0xFFFFFFFF;
    zstate = 0;
  }
  return 0xFF;
}