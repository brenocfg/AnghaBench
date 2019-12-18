#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ handler; scalar_t__ state; } ;
typedef  TYPE_2__ retro_task_t ;
struct TYPE_5__ {int /*<<< orphan*/  url; } ;
struct TYPE_7__ {TYPE_1__ connection; } ;
typedef  TYPE_3__ http_handle_t ;

/* Variables and functions */
 int string_is_equal (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ task_http_transfer_handler ; 

__attribute__((used)) static bool task_http_finder(retro_task_t *task, void *user_data)
{
   http_handle_t *http = NULL;

   if (!task || (task->handler != task_http_transfer_handler))
      return false;

   if (!user_data)
      return false;

   http = (http_handle_t*)task->state;
   if (!http)
      return false;

   return string_is_equal(http->connection.url, (const char*)user_data);
}