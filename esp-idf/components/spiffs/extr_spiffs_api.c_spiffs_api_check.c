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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  size_t spiffs_check_type ;
typedef  size_t spiffs_check_report ;
typedef  int /*<<< orphan*/  spiffs ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESP_LOGV (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t SPIFFS_CHECK_PROGRESS ; 
 int /*<<< orphan*/  TAG ; 

void spiffs_api_check(spiffs *fs, spiffs_check_type type, 
                            spiffs_check_report report, uint32_t arg1, uint32_t arg2)
{
    static const char * spiffs_check_type_str[3] = {
        "LOOKUP",
        "INDEX",
        "PAGE"
    };

    static const char * spiffs_check_report_str[7] = {
        "PROGRESS",
        "ERROR",
        "FIX INDEX",
        "FIX LOOKUP",
        "DELETE ORPHANED INDEX",
        "DELETE PAGE",
        "DELETE BAD FILE"
    };

    if (report != SPIFFS_CHECK_PROGRESS) {
        ESP_LOGE(TAG, "CHECK: type:%s, report:%s, %x:%x", spiffs_check_type_str[type], 
                              spiffs_check_report_str[report], arg1, arg2);
    } else {
        ESP_LOGV(TAG, "CHECK PROGRESS: report:%s, %x:%x", 
                              spiffs_check_report_str[report], arg1, arg2);
    }
}