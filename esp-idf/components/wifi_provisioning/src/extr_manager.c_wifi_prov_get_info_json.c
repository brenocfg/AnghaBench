#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cJSON ;
struct TYPE_4__ {scalar_t__ no_pop; scalar_t__ no_sec; } ;
struct TYPE_5__ {TYPE_1__ capabilities; int /*<<< orphan*/  version; } ;
struct TYPE_6__ {TYPE_2__ mgr_info; scalar_t__ app_info_json; } ;

/* Variables and functions */
 int /*<<< orphan*/  cJSON_AddItemToArray (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cJSON_AddItemToObject (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cJSON_AddStringToObject (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cJSON_CreateArray () ; 
 int /*<<< orphan*/ * cJSON_CreateObject () ; 
 int /*<<< orphan*/  cJSON_CreateString (char*) ; 
 int /*<<< orphan*/ * cJSON_Duplicate (scalar_t__,int) ; 
 TYPE_3__* prov_ctx ; 

__attribute__((used)) static cJSON* wifi_prov_get_info_json(void)
{
    cJSON *full_info_json = prov_ctx->app_info_json ?
                                cJSON_Duplicate(prov_ctx->app_info_json, 1) : cJSON_CreateObject();
    cJSON *prov_info_json = cJSON_CreateObject();
    cJSON *prov_capabilities = cJSON_CreateArray();

    /* Use label "prov" to indicate provisioning related information */
    cJSON_AddItemToObject(full_info_json, "prov", prov_info_json);

    /* Version field */
    cJSON_AddStringToObject(prov_info_json, "ver", prov_ctx->mgr_info.version);

    /* Capabilities field */
    cJSON_AddItemToObject(prov_info_json, "cap", prov_capabilities);

    /* If Security / Proof of Possession is not used, indicate in capabilities */
    if (prov_ctx->mgr_info.capabilities.no_sec) {
        cJSON_AddItemToArray(prov_capabilities, cJSON_CreateString("no_sec"));
    } else if (prov_ctx->mgr_info.capabilities.no_pop) {
        cJSON_AddItemToArray(prov_capabilities, cJSON_CreateString("no_pop"));
    }

    /* Indicate capability for performing Wi-Fi scan */
    cJSON_AddItemToArray(prov_capabilities, cJSON_CreateString("wifi_scan"));
    return full_info_json;
}