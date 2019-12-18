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
struct TYPE_3__ {scalar_t__ arg_size; void* arg; int /*<<< orphan*/  fn; } ;
typedef  TYPE_1__ wifi_ipc_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  esp_wifi_ipc_internal (TYPE_1__*,int) ; 
 int /*<<< orphan*/  hostap_eapol_resend_process ; 

void resend_eapol_handle(void *timeout_ctx)
{
    wifi_ipc_config_t cfg;

    cfg.fn = hostap_eapol_resend_process;
    cfg.arg = timeout_ctx;
    cfg.arg_size = 0;
    esp_wifi_ipc_internal(&cfg, false);
}