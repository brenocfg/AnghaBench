#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int instruction; TYPE_1__* operands; } ;
struct TYPE_3__ {int /*<<< orphan*/  present; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_t_pkhbt () ; 
 TYPE_2__ inst ; 

__attribute__((used)) static void
do_t_pkhtb (void)
{
  if (!inst.operands[3].present)
    inst.instruction &= ~0x00000020;
  do_t_pkhbt ();
}