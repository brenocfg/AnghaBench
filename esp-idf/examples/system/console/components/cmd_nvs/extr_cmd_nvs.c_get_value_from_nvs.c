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
typedef  int uint8_t ;
typedef  char* uint64_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  scalar_t__ nvs_type_t ;
typedef  int /*<<< orphan*/  nvs_handle_t ;
typedef  int int8_t ;
typedef  char* int64_t ;
typedef  int int32_t ;
typedef  int int16_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_NVS_TYPE_MISMATCH ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  NVS_READONLY ; 
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
 int /*<<< orphan*/  current_namespace ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (size_t) ; 
 int /*<<< orphan*/  nvs_close (int /*<<< orphan*/ ) ; 
 scalar_t__ nvs_get_blob (int /*<<< orphan*/ ,char const*,char*,size_t*) ; 
 scalar_t__ nvs_get_i16 (int /*<<< orphan*/ ,char const*,int*) ; 
 scalar_t__ nvs_get_i32 (int /*<<< orphan*/ ,char const*,int*) ; 
 scalar_t__ nvs_get_i64 (int /*<<< orphan*/ ,char const*,char**) ; 
 scalar_t__ nvs_get_i8 (int /*<<< orphan*/ ,char const*,int*) ; 
 scalar_t__ nvs_get_str (int /*<<< orphan*/ ,char const*,char*,size_t*) ; 
 scalar_t__ nvs_get_u16 (int /*<<< orphan*/ ,char const*,int*) ; 
 scalar_t__ nvs_get_u32 (int /*<<< orphan*/ ,char const*,int*) ; 
 scalar_t__ nvs_get_u64 (int /*<<< orphan*/ ,char const*,char**) ; 
 scalar_t__ nvs_get_u8 (int /*<<< orphan*/ ,char const*,int*) ; 
 scalar_t__ nvs_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_blob (char*,size_t) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ str_to_type (char const*) ; 

__attribute__((used)) static esp_err_t get_value_from_nvs(const char *key, const char *str_type)
{
    nvs_handle_t nvs;
    esp_err_t err;

    nvs_type_t type = str_to_type(str_type);

    if (type == NVS_TYPE_ANY) {
        ESP_LOGE(TAG, "Type '%s' is undefined", str_type);
        return ESP_ERR_NVS_TYPE_MISMATCH;
    }

    err = nvs_open(current_namespace, NVS_READONLY, &nvs);
    if (err != ESP_OK) {
        return err;
    }

    if (type == NVS_TYPE_I8) {
        int8_t value;
        err = nvs_get_i8(nvs, key, &value);
        if (err == ESP_OK) {
            printf("%d\n", value);
        }
    } else if (type == NVS_TYPE_U8) {
        uint8_t value;
        err = nvs_get_u8(nvs, key, &value);
        if (err == ESP_OK) {
            printf("%u\n", value);
        }
    } else if (type == NVS_TYPE_I16) {
        int16_t value;
        err = nvs_get_i16(nvs, key, &value);
        if (err == ESP_OK) {
            printf("%u\n", value);
        }
    } else if (type == NVS_TYPE_U16) {
        uint16_t value;
        if ((err = nvs_get_u16(nvs, key, &value)) == ESP_OK) {
            printf("%u\n", value);
        }
    } else if (type == NVS_TYPE_I32) {
        int32_t value;
        if ((err = nvs_get_i32(nvs, key, &value)) == ESP_OK) {
            printf("%d\n", value);
        }
    } else if (type == NVS_TYPE_U32) {
        uint32_t value;
        if ((err = nvs_get_u32(nvs, key, &value)) == ESP_OK) {
            printf("%u\n", value);
        }
    } else if (type == NVS_TYPE_I64) {
        int64_t value;
        if ((err = nvs_get_i64(nvs, key, &value)) == ESP_OK) {
            printf("%lld\n", value);
        }
    } else if (type == NVS_TYPE_U64) {
        uint64_t value;
        if ( (err = nvs_get_u64(nvs, key, &value)) == ESP_OK) {
            printf("%llu\n", value);
        }
    } else if (type == NVS_TYPE_STR) {
        size_t len;
        if ( (err = nvs_get_str(nvs, key, NULL, &len)) == ESP_OK) {
            char *str = (char *)malloc(len);
            if ( (err = nvs_get_str(nvs, key, str, &len)) == ESP_OK) {
                printf("%s\n", str);
            }
            free(str);
        }
    } else if (type == NVS_TYPE_BLOB) {
        size_t len;
        if ( (err = nvs_get_blob(nvs, key, NULL, &len)) == ESP_OK) {
            char *blob = (char *)malloc(len);
            if ( (err = nvs_get_blob(nvs, key, blob, &len)) == ESP_OK) {
                print_blob(blob, len);
            }
            free(blob);
        }
    }

    nvs_close(nvs);
    return err;
}