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
struct TYPE_3__ {int connected; void* data; int /*<<< orphan*/ * iface; } ;
typedef  TYPE_1__ joypad_connection_t ;

/* Variables and functions */

__attribute__((used)) static void set_end_of_list(joypad_connection_t *list, unsigned end)
{
  joypad_connection_t *entry = (joypad_connection_t *)&list[end];
  entry->connected = false;
  entry->iface = NULL;
  entry->data = (void *)0xdeadbeef;
}