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
 scalar_t__ gotWheelButtonDown ; 
 scalar_t__ gotWheelButtonUp ; 
 scalar_t__ gotWheelClick ; 
 scalar_t__ gotWheelDown ; 
 scalar_t__ gotWheelUp ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  report_result (int /*<<< orphan*/ ) ; 

void instruction()
{
  if (!gotWheelUp || !gotWheelButtonUp) printf("Please scroll the mouse wheel upwards by a single notch (slowly move your finger away from you towards the display).\n");
  else if (!gotWheelDown || !gotWheelButtonDown) printf("Please scroll the mouse wheel downwards by a single notch (slowly move your finger towards you).\n");
  else if (!gotWheelClick) printf("Please click the wheel button.\n");
  else if (gotWheelUp && gotWheelButtonUp && gotWheelDown && gotWheelButtonDown && gotWheelClick) report_result(0);
}