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
struct TYPE_3__ {int /*<<< orphan*/  ping_task_hdl; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ esp_ping_t ;
typedef  scalar_t__ esp_ping_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  PING_CHECK (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PING_FLAGS_START ; 
 int /*<<< orphan*/  err ; 
 int /*<<< orphan*/  xTaskNotifyGive (int /*<<< orphan*/ ) ; 

esp_err_t esp_ping_start(esp_ping_handle_t hdl)
{
    esp_err_t ret = ESP_OK;
    esp_ping_t *ep = (esp_ping_t *)hdl;
    PING_CHECK(ep, "ping handle can't be null", err, ESP_ERR_INVALID_ARG);
    ep->flags |= PING_FLAGS_START;
    xTaskNotifyGive(ep->ping_task_hdl);
    return ESP_OK;
err:
    return ret;
}