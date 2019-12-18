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
typedef  int pdso_t ;

/* Variables and functions */
 int /*<<< orphan*/ * FinalizeLine8bitM4 ; 
 int /*<<< orphan*/ * FinalizeLineM4 ; 
 int /*<<< orphan*/ * FinalizeLineRGB555M4 ; 
#define  PDF_8BIT 129 
#define  PDF_RGB555 128 

void PicoDrawSetOutputMode4(pdso_t which)
{
  switch (which)
  {
    case PDF_8BIT:   FinalizeLineM4 = FinalizeLine8bitM4; break;
    case PDF_RGB555: FinalizeLineM4 = FinalizeLineRGB555M4; break;
    default:         FinalizeLineM4 = NULL; break;
  }
}