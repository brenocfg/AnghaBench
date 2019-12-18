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
struct http_connection_t {char* scan; } ;

/* Variables and functions */

bool net_http_connection_iterate(struct http_connection_t *conn)
{
   if (!conn)
      return false;

   while (*conn->scan != '/' && *conn->scan != ':' && *conn->scan != '\0')
      conn->scan++;

   return true;
}