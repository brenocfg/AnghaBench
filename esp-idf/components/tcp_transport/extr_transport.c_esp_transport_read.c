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
struct TYPE_4__ {int (* _read ) (TYPE_1__*,char*,int,int) ;} ;

/* Variables and functions */
 int stub1 (TYPE_1__*,char*,int,int) ; 

int esp_transport_read(esp_transport_handle_t t, char *buffer, int len, int timeout_ms)
{
    if (t && t->_read) {
        return t->_read(t, buffer, len, timeout_ms);
    }
    return -1;
}