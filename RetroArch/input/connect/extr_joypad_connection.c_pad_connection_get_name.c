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
struct TYPE_5__ {int /*<<< orphan*/  data; TYPE_1__* iface; } ;
typedef  TYPE_2__ joypad_connection_t ;
struct TYPE_4__ {char const* (* get_name ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 char const* stub1 (int /*<<< orphan*/ ) ; 

const char* pad_connection_get_name(joypad_connection_t *joyconn, unsigned pad)
{
   if (!joyconn || !joyconn->iface || !joyconn->iface->get_name)
      return NULL;
   return joyconn->iface->get_name(joyconn->data);
}