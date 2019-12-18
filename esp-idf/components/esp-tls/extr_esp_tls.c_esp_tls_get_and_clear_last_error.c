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
typedef  int /*<<< orphan*/  esp_tls_last_error_t ;
typedef  TYPE_1__* esp_tls_error_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {int esp_tls_error_code; int esp_tls_flags; int /*<<< orphan*/  last_error; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

esp_err_t esp_tls_get_and_clear_last_error(esp_tls_error_handle_t h, int *esp_tls_code, int *esp_tls_flags)
{
    if (!h) {
        return ESP_ERR_INVALID_STATE;
    }
    esp_err_t last_err = h->last_error;
    if (esp_tls_code) {
        *esp_tls_code = h->esp_tls_error_code;
    }
    if (esp_tls_flags) {
        *esp_tls_flags = h->esp_tls_flags;
    }
    memset(h, 0, sizeof(esp_tls_last_error_t));
    return last_err;
}