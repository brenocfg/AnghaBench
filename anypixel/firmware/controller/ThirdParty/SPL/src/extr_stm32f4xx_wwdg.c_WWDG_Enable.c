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
typedef  int uint8_t ;
struct TYPE_2__ {int CR; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_WWDG_COUNTER (int) ; 
 TYPE_1__* WWDG ; 
 int WWDG_CR_WDGA ; 
 int /*<<< orphan*/  assert_param (int /*<<< orphan*/ ) ; 

void WWDG_Enable(uint8_t Counter)
{
  /* Check the parameters */
  assert_param(IS_WWDG_COUNTER(Counter));
  WWDG->CR = WWDG_CR_WDGA | Counter;
}