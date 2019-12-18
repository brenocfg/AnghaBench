#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* name; int /*<<< orphan*/  dispatch_method; int /*<<< orphan*/ * arg; int /*<<< orphan*/  callback; } ;
typedef  TYPE_1__ esp_timer_create_args_t ;
typedef  scalar_t__ esp_err_t ;
struct TYPE_5__ {int /*<<< orphan*/  timer_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_TIMER_TASK ; 
 int /*<<< orphan*/  MDNS_TIMER_PERIOD_US ; 
 TYPE_3__* _mdns_server ; 
 int /*<<< orphan*/  _mdns_timer_cb ; 
 scalar_t__ esp_timer_create (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ esp_timer_start_periodic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t _mdns_start_timer(void){
    esp_timer_create_args_t timer_conf = {
        .callback = _mdns_timer_cb,
        .arg = NULL,
        .dispatch_method = ESP_TIMER_TASK,
        .name = "mdns_timer"
    };
    esp_err_t err = esp_timer_create(&timer_conf, &(_mdns_server->timer_handle));
    if (err) {
        return err;
    }
    return esp_timer_start_periodic(_mdns_server->timer_handle, MDNS_TIMER_PERIOD_US);
}