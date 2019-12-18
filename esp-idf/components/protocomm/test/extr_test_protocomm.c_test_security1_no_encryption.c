#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_10__ {int id; int sec_ver; TYPE_2__* pop; } ;
typedef  TYPE_1__ session_t ;
struct TYPE_11__ {int /*<<< orphan*/  len; int /*<<< orphan*/  const* data; } ;
typedef  TYPE_2__ protocomm_security_pop_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 scalar_t__ ESP_ERR_NO_MEM ; 
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ start_test_service (int,TYPE_2__*) ; 
 int /*<<< orphan*/  stop_test_service () ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  test_delete_session (TYPE_1__*) ; 
 scalar_t__ test_new_session (TYPE_1__*) ; 
 scalar_t__ test_req_endpoint (TYPE_1__*) ; 
 scalar_t__ test_sec_endpoint (TYPE_1__*) ; 

__attribute__((used)) static esp_err_t test_security1_no_encryption (void)
{
    ESP_LOGI(TAG, "Starting Security 1 no encryption test");

    const char *pop_data = "test pop";
    protocomm_security_pop_t pop = {
        .data = (const uint8_t *)pop_data,
        .len  = strlen(pop_data)
    };

    session_t *session = calloc(1, sizeof(session_t));
    if (session == NULL) {
        ESP_LOGE(TAG, "Error allocating session");
        return ESP_ERR_NO_MEM;
    }

    session->id        = 1;
    session->sec_ver   = 1;
    session->pop       = &pop;

    // Start protocomm service
    if (start_test_service(1, &pop) != ESP_OK) {
        ESP_LOGE(TAG, "Error starting test");
        free(session);
        return ESP_ERR_INVALID_STATE;
    }

    // Intialise protocomm session with zero public keys
    if (test_new_session(session) != ESP_OK) {
        ESP_LOGE(TAG, "Error creating new session");
        stop_test_service();
        free(session);
        return ESP_FAIL;
    }

    // Perform 25519 security handshake to set public keys
    if (test_sec_endpoint(session) != ESP_OK) {
        ESP_LOGE(TAG, "Error testing security endpoint");
        test_delete_session(session);
        stop_test_service();
        free(session);
        return ESP_FAIL;
    }

    // Force endpoint with un-encrypted data
    session->sec_ver = 0;

    // Send unencrypted request data to echo endpoint.
    // Response would be encrypted causing echoed back
    // data to not match that which was sent, hence failing.
    if (test_req_endpoint(session) == ESP_OK) {
        ESP_LOGE(TAG, "Error testing request endpoint");
        session->sec_ver = 1;
        test_delete_session(session);
        stop_test_service();
        free(session);
        return ESP_FAIL;
    }

    session->sec_ver = 1;
    test_delete_session(session);
    stop_test_service();
    free(session);
    ESP_LOGI(TAG, "Protocomm test successful");
    return ESP_OK;
}