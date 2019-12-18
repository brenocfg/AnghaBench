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
struct TYPE_3__ {void* error_callback_data; int /*<<< orphan*/  error_callback; } ;
typedef  TYPE_1__ ILCLIENT_T ;
typedef  int /*<<< orphan*/  ILCLIENT_CALLBACK_T ;

/* Variables and functions */

void ilclient_set_error_callback(ILCLIENT_T *st, ILCLIENT_CALLBACK_T func, void *userdata)
{
   st->error_callback = func;
   st->error_callback_data = userdata;
}