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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  WINR; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_IWDG_WINDOW_VALUE (int /*<<< orphan*/ ) ; 
 TYPE_1__* IWDG ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void IWDG_SetWindowValue(uint16_t WindowValue)
{
  /* Check the parameters */
  assert_param(IS_IWDG_WINDOW_VALUE(WindowValue));
  IWDG->WINR = WindowValue;
}