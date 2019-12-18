#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* esp_transport_handle_t ;
struct TYPE_6__ {TYPE_1__* (* _parent_transfer ) (TYPE_1__*) ;scalar_t__ _read; } ;

/* Variables and functions */
 TYPE_1__* stub1 (TYPE_1__*) ; 

esp_transport_handle_t esp_transport_get_payload_transport_handle(esp_transport_handle_t t)
{
    if (t && t->_read) {
        return t->_parent_transfer(t);
    }
    return NULL;
}