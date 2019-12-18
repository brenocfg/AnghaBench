#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pop; int /*<<< orphan*/  sec_ver; } ;
typedef  TYPE_1__ session_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_FAIL ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ start_test_service (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_test_service () ; 
 int /*<<< orphan*/  test_delete_session (TYPE_1__*) ; 
 scalar_t__ test_new_session (TYPE_1__*) ; 
 scalar_t__ test_req_endpoint (TYPE_1__*) ; 
 scalar_t__ test_sec_endpoint (TYPE_1__*) ; 
 scalar_t__ test_ver_endpoint (TYPE_1__*) ; 

__attribute__((used)) static esp_err_t test_protocomm (session_t *session)
{
    ESP_LOGI(TAG, "Starting Protocomm test");

    // Start protocomm service
    if (start_test_service(session->sec_ver, session->pop) != ESP_OK) {
        ESP_LOGE(TAG, "Error starting test");
        return ESP_FAIL;
    }

    // Check version endpoint
    if (test_ver_endpoint(session) != ESP_OK) {
        ESP_LOGE(TAG, "Error testing version endpoint");
        stop_test_service();
        return ESP_FAIL;
    }

    // Intialise protocomm session with zero public keys
    if (test_new_session(session) != ESP_OK) {
        ESP_LOGE(TAG, "Error creating new session");
        stop_test_service();
        return ESP_FAIL;
    }

    // Perform 25519 security handshake to set public keys
    if (test_sec_endpoint(session) != ESP_OK) {
        ESP_LOGE(TAG, "Error testing security endpoint");
        test_delete_session(session);
        stop_test_service();
        return ESP_FAIL;
    }

    // Send request data to echo endpoint encrypted with
    // the set public keys on both client and server side
    if (test_req_endpoint(session) != ESP_OK) {
        ESP_LOGE(TAG, "Error testing request endpoint");
        test_delete_session(session);
        stop_test_service();
        return ESP_FAIL;
    }

    // Stop protocomm service
    test_delete_session(session);
    stop_test_service();
    ESP_LOGI(TAG, "Protocomm test successful");
    return ESP_OK;
}