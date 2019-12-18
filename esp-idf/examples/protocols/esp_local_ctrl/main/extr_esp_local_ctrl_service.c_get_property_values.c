#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_5__ {int /*<<< orphan*/  free_fn; int /*<<< orphan*/ * data; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ esp_local_ctrl_prop_val_t ;
struct TYPE_6__ {int type; int /*<<< orphan*/ * ctx; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ esp_local_ctrl_prop_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_NO_MEM ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_OK ; 
#define  PROP_TYPE_BOOLEAN 131 
#define  PROP_TYPE_INT32 130 
#define  PROP_TYPE_STRING 129 
#define  PROP_TYPE_TIMESTAMP 128 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  esp_timer_get_time () ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static esp_err_t get_property_values(size_t props_count,
                                     const esp_local_ctrl_prop_t props[],
                                     esp_local_ctrl_prop_val_t prop_values[],
                                     void *usr_ctx)
{
    for (uint32_t i = 0; i < props_count; i++) {
        ESP_LOGI(TAG, "Reading property : %s", props[i].name);
        /* For the purpose of this example, to keep things simple
         * we have set the context pointer of each property to
         * point to its value (except for timestamp) */
        switch (props[i].type) {
            case PROP_TYPE_INT32:
            case PROP_TYPE_BOOLEAN:
                /* No need to set size for these types as sizes where
                 * specified when declaring the properties, unlike for
                 * string type. */
                prop_values[i].data = props[i].ctx;
                break;
            case PROP_TYPE_TIMESTAMP: {
                /* Get the time stamp */
                static int64_t ts = 0;
                ts = esp_timer_get_time();

                /* Set the current time. Since this is statically
                 * allocated, we don't need to provide a free_fn */
                prop_values[i].data = &ts;
                break;
            }
            case PROP_TYPE_STRING: {
                char **prop3_value = (char **) props[i].ctx;
                if (*prop3_value == NULL) {
                    prop_values[i].size = 0;
                    prop_values[i].data = NULL;
                } else {
                    /* We could try dynamically allocating the output value,
                     * and it should get freed automatically after use, as
                     * `esp_local_ctrl` internally calls the provided `free_fn` */
                    prop_values[i].size = strlen(*prop3_value);
                    prop_values[i].data = strdup(*prop3_value);
                    if (!prop_values[i].data) {
                        return ESP_ERR_NO_MEM;
                    }
                    prop_values[i].free_fn = free;
                }
            }
            default:
                break;
        }
    }
    return ESP_OK;
}