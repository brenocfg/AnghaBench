#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  nvs_handle_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 scalar_t__ ESP_ERR_NVS_NOT_FOUND ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  NVS_READWRITE ; 
 int UINT16_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  nvs_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvs_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvs_flash_init () ; 
 scalar_t__ nvs_get_u32 (int /*<<< orphan*/ ,char const*,int*) ; 
 int /*<<< orphan*/  nvs_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvs_set_u32 (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int ulp_edge_count ; 

__attribute__((used)) static void update_pulse_count(void)
{
    const char* namespace = "plusecnt";
    const char* count_key = "count";

    ESP_ERROR_CHECK( nvs_flash_init() );
    nvs_handle_t handle;
    ESP_ERROR_CHECK( nvs_open(namespace, NVS_READWRITE, &handle));
    uint32_t pulse_count = 0;
    esp_err_t err = nvs_get_u32(handle, count_key, &pulse_count);
    assert(err == ESP_OK || err == ESP_ERR_NVS_NOT_FOUND);
    printf("Read pulse count from NVS: %5d\n", pulse_count);

    /* ULP program counts signal edges, convert that to the number of pulses */
    uint32_t pulse_count_from_ulp = (ulp_edge_count & UINT16_MAX) / 2;
    /* In case of an odd number of edges, keep one until next time */
    ulp_edge_count = ulp_edge_count % 2;
    printf("Pulse count from ULP: %5d\n", pulse_count_from_ulp);

    /* Save the new pulse count to NVS */
    pulse_count += pulse_count_from_ulp;
    ESP_ERROR_CHECK(nvs_set_u32(handle, count_key, pulse_count));
    ESP_ERROR_CHECK(nvs_commit(handle));
    nvs_close(handle);
    printf("Wrote updated pulse count to NVS: %5d\n", pulse_count);
}