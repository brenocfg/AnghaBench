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
 scalar_t__ gotClick ; 
 scalar_t__ gotDblClick ; 
 scalar_t__ gotMouseDown ; 
 scalar_t__ gotMouseMove ; 
 scalar_t__ gotMouseUp ; 
 scalar_t__ gotWheel ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  report_result (int /*<<< orphan*/ ) ; 

void instruction()
{
  if (!gotClick) { printf("Please click on the canvas.\n"); return; }
  if (!gotMouseDown) { printf("Please click on the canvas.\n"); return; }
  if (!gotMouseUp) { printf("Please click on the canvas.\n"); return; }
  if (!gotDblClick) { printf("Please double-click on the canvas.\n"); return; }
  if (!gotMouseMove) { printf("Please move the mouse on the canvas.\n"); return; }
  if (!gotWheel) { printf("Please scroll the mouse wheel.\n"); return; }

  if (gotClick && gotMouseDown && gotMouseUp && gotDblClick && gotMouseMove && gotWheel) report_result(0);
}