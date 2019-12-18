#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  retro_task_callback_t ;

/* Variables and functions */
 int /*<<< orphan*/  net_http_connection_new (char const*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ string_is_empty (char const*) ; 
 void* task_push_http_transfer_generic (int /*<<< orphan*/ ,char const*,int,char const*,int /*<<< orphan*/ ,void*) ; 

void* task_push_http_transfer(const char *url, bool mute,
      const char *type,
      retro_task_callback_t cb, void *user_data)
{
   if (string_is_empty(url))
      return NULL;
   return task_push_http_transfer_generic(
         net_http_connection_new(url, "GET", NULL),
         url, mute, type, cb, user_data);
}