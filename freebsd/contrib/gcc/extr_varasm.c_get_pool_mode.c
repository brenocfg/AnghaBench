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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_2__ {int mode; } ;

/* Variables and functions */
 TYPE_1__* SYMBOL_REF_CONSTANT (int /*<<< orphan*/ ) ; 

enum machine_mode
get_pool_mode (rtx addr)
{
  return SYMBOL_REF_CONSTANT (addr)->mode;
}