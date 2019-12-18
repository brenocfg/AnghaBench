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
struct TYPE_3__ {void* fill_buffer_done_callback_data; int /*<<< orphan*/  fill_buffer_done_callback; } ;
typedef  TYPE_1__ ILCLIENT_T ;
typedef  int /*<<< orphan*/  ILCLIENT_BUFFER_CALLBACK_T ;

/* Variables and functions */

void ilclient_set_fill_buffer_done_callback(ILCLIENT_T *st, ILCLIENT_BUFFER_CALLBACK_T func, void *userdata)
{
   st->fill_buffer_done_callback = func;
   st->fill_buffer_done_callback_data = userdata;
}