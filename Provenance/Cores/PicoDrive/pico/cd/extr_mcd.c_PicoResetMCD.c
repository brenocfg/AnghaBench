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
struct TYPE_2__ {scalar_t__ end; scalar_t__ start; scalar_t__ size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int POPT_EN_MCD_RAMCART ; 
 int PicoOpt ; 
 TYPE_1__ SRam ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

int PicoResetMCD(void)
{
  // reset button doesn't affect MCD hardware

  // use SRam.data for RAM cart
  if (PicoOpt & POPT_EN_MCD_RAMCART) {
    if (SRam.data == NULL)
      SRam.data = calloc(1, 0x12000);
  }
  else if (SRam.data != NULL) {
    free(SRam.data);
    SRam.data = NULL;
      SRam.size = 0;
  }
  SRam.start = SRam.end = 0; // unused

  return 0;
}