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
struct http_connection_t {int dummy; } ;
typedef  int /*<<< orphan*/  retro_task_callback_t ;

/* Variables and functions */
 struct http_connection_t* net_http_connection_new (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  net_http_connection_set_user_agent (struct http_connection_t*,char const*) ; 
 scalar_t__ string_is_empty (char const*) ; 
 void* task_push_http_transfer_generic (struct http_connection_t*,char const*,int,char const*,int /*<<< orphan*/ ,void*) ; 

void* task_push_http_transfer_with_user_agent(const char *url, bool mute,
   const char *type, const char* user_agent,
   retro_task_callback_t cb, void *user_data)
{
   struct http_connection_t* conn;

   if (string_is_empty(url))
      return NULL;

   conn = net_http_connection_new(url, "GET", NULL);
   if (!conn)
      return NULL;

   if (user_agent != NULL)
      net_http_connection_set_user_agent(conn, user_agent);

   /* assert: task_push_http_transfer_generic will free conn on failure */
   return task_push_http_transfer_generic(conn, url, mute, type, cb, user_data);
}