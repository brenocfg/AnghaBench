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
struct TYPE_2__ {char const* ident; } ;

/* Variables and functions */
 TYPE_1__* menu_driver_ctx ; 
 int /*<<< orphan*/  menu_driver_is_alive () ; 

const char *menu_driver_ident(void)
{
   if (!menu_driver_is_alive())
      return NULL;
   if (!menu_driver_ctx || !menu_driver_ctx->ident)
      return NULL;
  return menu_driver_ctx->ident;
}