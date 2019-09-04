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
struct TYPE_2__ {int /*<<< orphan*/  CR; } ;

/* Variables and functions */
 TYPE_1__* CRC ; 
 int /*<<< orphan*/  CRC_CR_RESET ; 

void CRC_ResetDR(void)
{
  /* Reset CRC generator */
  CRC->CR = CRC_CR_RESET;
}