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
struct TYPE_2__ {int /*<<< orphan*/  box_message; } ;
typedef  TYPE_1__ xmb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  strdup (char const*) ; 
 scalar_t__ string_is_empty (char const*) ; 

__attribute__((used)) static void xmb_messagebox(void *data, const char *message)
{
   xmb_handle_t *xmb = (xmb_handle_t*)data;

   if (!xmb || string_is_empty(message))
      return;

   xmb->box_message = strdup(message);
}