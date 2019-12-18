#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ enum_idx; } ;
typedef  TYPE_1__ menu_entry_t ;

/* Variables and functions */
 scalar_t__ MENU_ENUM_LABEL_CHEEVOS_PASSWORD ; 

bool menu_entry_is_password(menu_entry_t *entry)
{
   return entry->enum_idx == MENU_ENUM_LABEL_CHEEVOS_PASSWORD;
}