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
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_2__ {int /*<<< orphan*/  fcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  save_param (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ slot ; 

int sms_cart_context_save(uint8 *state)
{
  int bufferptr = 0;
  save_param(slot.fcr, 4);
  return bufferptr;
}