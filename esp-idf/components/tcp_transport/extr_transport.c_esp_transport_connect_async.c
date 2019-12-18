#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* esp_transport_handle_t ;
struct TYPE_4__ {int (* _connect_async ) (TYPE_1__*,char const*,int,int) ;} ;

/* Variables and functions */
 int stub1 (TYPE_1__*,char const*,int,int) ; 

int esp_transport_connect_async(esp_transport_handle_t t, const char *host, int port, int timeout_ms)
{
    int ret = -1;
    if (t && t->_connect_async) {
        return t->_connect_async(t, host, port, timeout_ms);
    }
    return ret;
}