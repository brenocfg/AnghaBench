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
struct TYPE_3__ {int /*<<< orphan*/ * carthw; } ;
struct TYPE_4__ {TYPE_1__ ms; } ;

/* Variables and functions */
 TYPE_2__ Pico ; 
 int /*<<< orphan*/  write_bank (int,int /*<<< orphan*/ ) ; 

void PicoStateLoadedMS(void)
{
  write_bank(0xfffe, Pico.ms.carthw[0x0e]);
  write_bank(0xffff, Pico.ms.carthw[0x0f]);
}