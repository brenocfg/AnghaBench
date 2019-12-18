#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int id; } ;
typedef  TYPE_1__ session_t ;
typedef  scalar_t__ protocomm_security_handle_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ calloc (int,int) ; 

__attribute__((used)) static esp_err_t sec1_init(protocomm_security_handle_t *handle)
{
    if (!handle) {
        return ESP_ERR_INVALID_ARG;
    }
    session_t *cur_session = (session_t *) calloc(1, sizeof(session_t));
    if (!cur_session) {
        ESP_LOGE(TAG, "Error allocating new session");
        return ESP_ERR_NO_MEM;
    }
    cur_session->id = -1;
    *handle = (protocomm_security_handle_t) cur_session;
    return ESP_OK;
}