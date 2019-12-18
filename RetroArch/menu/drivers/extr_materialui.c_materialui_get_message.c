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
struct TYPE_2__ {char* msgbox; } ;
typedef  TYPE_1__ materialui_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

__attribute__((used)) static void materialui_get_message(void *data, const char *message)
{
   materialui_handle_t *mui   = (materialui_handle_t*)data;

   if (!mui || !message || !*message)
      return;

   mui->msgbox[0] = '\0';

   if (!string_is_empty(message))
      strlcpy(mui->msgbox, message, sizeof(mui->msgbox));
}