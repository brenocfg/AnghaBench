#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  handle; } ;
struct TYPE_4__ {int error; int /*<<< orphan*/ * cb; int /*<<< orphan*/  handle; TYPE_1__ connection; } ;
typedef  TYPE_2__ http_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  net_http_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_init () ; 

__attribute__((used)) static int cb_http_conn_default(void *data_, size_t len)
{
   http_handle_t *http = (http_handle_t*)data_;

   if (!http)
      return -1;

   if (!network_init())
      return -1;

   http->handle = net_http_new(http->connection.handle);

   if (!http->handle)
   {
      http->error = true;
      return -1;
   }

   http->cb     = NULL;

   return 0;
}