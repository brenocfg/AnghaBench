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
typedef  scalar_t__ pdso_t ;
struct TYPE_2__ {void* pal_native; } ;

/* Variables and functions */
 scalar_t__ PDF_RGB555 ; 
 int /*<<< orphan*/  PDM32X_32X_ONLY ; 
 int /*<<< orphan*/  PDM32X_BOTH ; 
 int /*<<< orphan*/  PDM32X_OFF ; 
 int /*<<< orphan*/  Pico32xDrawMode ; 
 TYPE_1__* Pico32xMem ; 
 int /*<<< orphan*/ * PicoDraw2FB ; 
 int /*<<< orphan*/  PicoDrawSetInternalBuf (int /*<<< orphan*/ *,int) ; 

void PicoDrawSetOutFormat32x(pdso_t which, int use_32x_line_mode)
{
#ifdef _ASM_32X_DRAW
  extern void *Pico32xNativePal;
  Pico32xNativePal = Pico32xMem->pal_native;
#endif

  if (which == PDF_RGB555 && use_32x_line_mode) {
    // we'll draw via FinalizeLine32xRGB555 (rare)
    PicoDrawSetInternalBuf(NULL, 0);
    Pico32xDrawMode = PDM32X_OFF;
    return;
  }

  // use the same layout as alt renderer
  PicoDrawSetInternalBuf(PicoDraw2FB, 328);
  Pico32xDrawMode = (which == PDF_RGB555) ? PDM32X_32X_ONLY : PDM32X_BOTH;
}