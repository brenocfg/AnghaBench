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

/* Variables and functions */
 int /*<<< orphan*/  PAHW_32X ; 
 int /*<<< orphan*/ * Pico32xMem ; 
 int /*<<< orphan*/  PicoAHW ; 
 int /*<<< orphan*/  msh2 ; 
 int /*<<< orphan*/  plat_munmap (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sh2_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssh2 ; 

void PicoUnload32x(void)
{
  if (Pico32xMem != NULL)
    plat_munmap(Pico32xMem, sizeof(*Pico32xMem));
  Pico32xMem = NULL;
  sh2_finish(&msh2);
  sh2_finish(&ssh2);

  PicoAHW &= ~PAHW_32X;
}