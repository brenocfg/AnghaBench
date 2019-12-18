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
typedef  void* trans_func ;
typedef  void* poll_func ;
typedef  int /*<<< orphan*/  io_read_func ;
typedef  int /*<<< orphan*/  io_func ;
typedef  TYPE_1__* esp_transport_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  connect_func ;
struct TYPE_3__ {int /*<<< orphan*/  _parent_transfer; int /*<<< orphan*/ * _connect_async; void* _destroy; void* _poll_write; void* _poll_read; void* _close; int /*<<< orphan*/  _write; int /*<<< orphan*/  _read; int /*<<< orphan*/  _connect; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  esp_transport_get_default_parent ; 

esp_err_t esp_transport_set_func(esp_transport_handle_t t,
                             connect_func _connect,
                             io_read_func _read,
                             io_func _write,
                             trans_func _close,
                             poll_func _poll_read,
                             poll_func _poll_write,
                             trans_func _destroy)
{
    if (t == NULL) {
        return ESP_FAIL;
    }
    t->_connect = _connect;
    t->_read = _read;
    t->_write = _write;
    t->_close = _close;
    t->_poll_read = _poll_read;
    t->_poll_write = _poll_write;
    t->_destroy = _destroy;
    t->_connect_async = NULL;
    t->_parent_transfer = esp_transport_get_default_parent;
    return ESP_OK;
}