#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cycles; } ;

/* Variables and functions */
 int /*<<< orphan*/  CycloneRun (TYPE_1__*) ; 
 TYPE_1__* currentC68k ; 
 int fm68k_emulate (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int otherRun(void)
{
#if defined(EMU_C68K)
  currentC68k->cycles=1;
  CycloneRun(currentC68k);
  return 1-currentC68k->cycles;
#elif defined(EMU_F68K)
  return fm68k_emulate(1, 0);
#endif
}