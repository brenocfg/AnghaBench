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
typedef  int /*<<< orphan*/  mdns_result_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  MDNS_TYPE_TXT ; 
 scalar_t__ _str_null_or_empty (char const*) ; 
 int /*<<< orphan*/  mdns_query (char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 

esp_err_t mdns_query_txt(const char * instance, const char * service, const char * proto, uint32_t timeout, mdns_result_t ** result)
{
    if (_str_null_or_empty(instance) || _str_null_or_empty(service) || _str_null_or_empty(proto)) {
        return ESP_ERR_INVALID_ARG;
    }

    return mdns_query(instance, service, proto, MDNS_TYPE_TXT, timeout, 1, result);
}