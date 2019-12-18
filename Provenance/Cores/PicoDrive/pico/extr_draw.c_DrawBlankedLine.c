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
 int /*<<< orphan*/  BackFill (int,int) ; 
 char* DrawLineDest ; 
 int DrawLineDestIncrement ; 
 int /*<<< orphan*/  FinalizeLine (int,int) ; 
 int /*<<< orphan*/  HighCol ; 
 scalar_t__ HighColIncrement ; 
 int /*<<< orphan*/  PicoScanBegin (int) ; 
 int /*<<< orphan*/  PicoScanEnd (int) ; 

__attribute__((used)) static void DrawBlankedLine(int line, int offs, int sh, int bgc)
{
  if (PicoScanBegin != NULL)
    PicoScanBegin(line + offs);

  BackFill(bgc, sh);

  if (FinalizeLine != NULL)
    FinalizeLine(sh, line);

  if (PicoScanEnd != NULL)
    PicoScanEnd(line + offs);

  HighCol += HighColIncrement;
  DrawLineDest = (char *)DrawLineDest + DrawLineDestIncrement;
}