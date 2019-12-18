#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wiiu_hid_t ;
struct TYPE_5__ {int /*<<< orphan*/  data; TYPE_1__* iface; } ;
typedef  TYPE_2__ joypad_connection_t ;
struct TYPE_4__ {char const* (* get_name ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_2__* get_pad (int /*<<< orphan*/ *,unsigned int) ; 
 char const* stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const char *wiiu_hid_joypad_name(void *data, unsigned slot)
{
   joypad_connection_t *pad = get_pad((wiiu_hid_t *)data, slot);

   if (!pad)
      return NULL;

   return pad->iface->get_name(pad->data);
}