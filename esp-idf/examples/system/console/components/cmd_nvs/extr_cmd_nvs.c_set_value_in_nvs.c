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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ nvs_type_t ;
typedef  int /*<<< orphan*/  nvs_handle_t ;
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int64_t ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ERANGE ; 
 scalar_t__ ESP_ERR_NVS_TYPE_MISMATCH ; 
 scalar_t__ ESP_ERR_NVS_VALUE_TOO_LONG ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ ESP_OK ; 
 scalar_t__ INT16_MAX ; 
 scalar_t__ INT16_MIN ; 
 scalar_t__ INT8_MAX ; 
 scalar_t__ INT8_MIN ; 
 int /*<<< orphan*/  NVS_READWRITE ; 
 scalar_t__ NVS_TYPE_ANY ; 
 scalar_t__ NVS_TYPE_BLOB ; 
 scalar_t__ NVS_TYPE_I16 ; 
 scalar_t__ NVS_TYPE_I32 ; 
 scalar_t__ NVS_TYPE_I64 ; 
 scalar_t__ NVS_TYPE_I8 ; 
 scalar_t__ NVS_TYPE_STR ; 
 scalar_t__ NVS_TYPE_U16 ; 
 scalar_t__ NVS_TYPE_U32 ; 
 scalar_t__ NVS_TYPE_U64 ; 
 scalar_t__ NVS_TYPE_U8 ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ UINT16_MAX ; 
 scalar_t__ UINT8_MAX ; 
 int /*<<< orphan*/  current_namespace ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  nvs_close (int /*<<< orphan*/ ) ; 
 scalar_t__ nvs_commit (int /*<<< orphan*/ ) ; 
 scalar_t__ nvs_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nvs_set_i16 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ nvs_set_i32 (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 scalar_t__ nvs_set_i64 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ nvs_set_i8 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ nvs_set_str (int /*<<< orphan*/ ,char const*,char const*) ; 
 scalar_t__ nvs_set_u16 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ nvs_set_u32 (int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 scalar_t__ nvs_set_u64 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ nvs_set_u8 (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ store_blob (int /*<<< orphan*/ ,char const*,char const*) ; 
 scalar_t__ str_to_type (char const*) ; 
 scalar_t__ strtol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoll (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strtoul (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strtoull (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static esp_err_t set_value_in_nvs(const char *key, const char *str_type, const char *str_value)
{
    esp_err_t err;
    nvs_handle_t nvs;
    bool range_error = false;

    nvs_type_t type = str_to_type(str_type);

    if (type == NVS_TYPE_ANY) {
        ESP_LOGE(TAG, "Type '%s' is undefined", str_type);
        return ESP_ERR_NVS_TYPE_MISMATCH;
    }

    err = nvs_open(current_namespace, NVS_READWRITE, &nvs);
    if (err != ESP_OK) {
        return err;
    }

    if (type == NVS_TYPE_I8) {
        int32_t value = strtol(str_value, NULL, 0);
        if (value < INT8_MIN || value > INT8_MAX || errno == ERANGE) {
            range_error = true;
        } else {
            err = nvs_set_i8(nvs, key, (int8_t)value);
        }
    } else if (type == NVS_TYPE_U8) {
        uint32_t value = strtoul(str_value, NULL, 0);
        if (value > UINT8_MAX || errno == ERANGE) {
            range_error = true;
        } else {
            err = nvs_set_u8(nvs, key, (uint8_t)value);
        }
    } else if (type == NVS_TYPE_I16) {
        int32_t value = strtol(str_value, NULL, 0);
        if (value < INT16_MIN || value > INT16_MAX || errno == ERANGE) {
            range_error = true;
        } else {
            err = nvs_set_i16(nvs, key, (int16_t)value);
        }
    } else if (type == NVS_TYPE_U16) {
        uint32_t value = strtoul(str_value, NULL, 0);
        if (value > UINT16_MAX || errno == ERANGE) {
            range_error = true;
        } else {
            err = nvs_set_u16(nvs, key, (uint16_t)value);
        }
    } else if (type == NVS_TYPE_I32) {
        int32_t value = strtol(str_value, NULL, 0);
        if (errno != ERANGE) {
            err = nvs_set_i32(nvs, key, value);
        }
    } else if (type == NVS_TYPE_U32) {
        uint32_t value = strtoul(str_value, NULL, 0);
        if (errno != ERANGE) {
            err = nvs_set_u32(nvs, key, value);
        }
    } else if (type == NVS_TYPE_I64) {
        int64_t value = strtoll(str_value, NULL, 0);
        if (errno != ERANGE) {
            err = nvs_set_i64(nvs, key, value);
        }
    } else if (type == NVS_TYPE_U64) {
        uint64_t value = strtoull(str_value, NULL, 0);
        if (errno != ERANGE) {
            err = nvs_set_u64(nvs, key, value);
        }
    } else if (type == NVS_TYPE_STR) {
        err = nvs_set_str(nvs, key, str_value);
    } else if (type == NVS_TYPE_BLOB) {
        err = store_blob(nvs, key, str_value);
    }

    if (range_error || errno == ERANGE) {
        nvs_close(nvs);
        return ESP_ERR_NVS_VALUE_TOO_LONG;
    }

    if (err == ESP_OK) {
        err = nvs_commit(nvs);
        if (err == ESP_OK) {
            ESP_LOGI(TAG, "Value stored under key '%s'", key);
        }
    }

    nvs_close(nvs);
    return err;
}