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
struct TYPE_2__ {char* msgbox; int force_redraw; } ;
typedef  TYPE_1__ rgui_t ;

/* Variables and functions */
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static void rgui_set_message(void *data, const char *message)
{
   rgui_t           *rgui = (rgui_t*)data;

   if (!rgui || !message)
      return;

   rgui->msgbox[0] = '\0';

   if (!string_is_empty(message))
      strlcpy(rgui->msgbox, message, sizeof(rgui->msgbox));

   rgui->force_redraw = true;
}