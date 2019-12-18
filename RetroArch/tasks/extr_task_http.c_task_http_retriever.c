#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ state; } ;
typedef  TYPE_2__ retro_task_t ;
struct TYPE_9__ {int /*<<< orphan*/  progress; int /*<<< orphan*/  url; } ;
typedef  TYPE_3__ http_transfer_info_t ;
struct TYPE_7__ {int /*<<< orphan*/  url; } ;
struct TYPE_10__ {TYPE_1__ connection; } ;
typedef  TYPE_4__ http_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  task_get_progress (TYPE_2__*) ; 

__attribute__((used)) static bool task_http_retriever(retro_task_t *task, void *data)
{
   http_transfer_info_t *info = (http_transfer_info_t*)data;

   /* Extract HTTP handle and return already if invalid */
   http_handle_t        *http = (http_handle_t *)task->state;
   if (!http)
      return false;

   /* Fill HTTP info link */
   strlcpy(info->url, http->connection.url, sizeof(info->url));
   info->progress = task_get_progress(task);
   return true;
}