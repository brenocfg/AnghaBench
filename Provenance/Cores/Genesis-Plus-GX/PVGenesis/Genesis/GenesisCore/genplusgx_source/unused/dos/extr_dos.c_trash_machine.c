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
struct TYPE_2__ {scalar_t__ sound; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFX_TEXT ; 
 int /*<<< orphan*/  clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_bitmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_bmp ; 
 int /*<<< orphan*/  msdos_shutdown_sound () ; 
 TYPE_1__ option ; 
 int /*<<< orphan*/  screen ; 
 int /*<<< orphan*/  set_gfx_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void trash_machine(void)
{
  if(option.sound)
  {
    msdos_shutdown_sound();
  }
  clear(screen);
  destroy_bitmap(gen_bmp);
  set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
}