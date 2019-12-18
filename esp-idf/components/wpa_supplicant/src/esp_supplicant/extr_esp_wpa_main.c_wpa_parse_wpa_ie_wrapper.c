#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* mgmt_group_cipher; int /*<<< orphan*/  pmkid; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  key_mgmt; void* group_cipher; void* pairwise_cipher; int /*<<< orphan*/  proto; } ;
typedef  TYPE_1__ wifi_wpa_ie_t ;
typedef  int /*<<< orphan*/  u8 ;
struct wpa_ie_data {int /*<<< orphan*/  mgmt_group_cipher; int /*<<< orphan*/  pmkid; int /*<<< orphan*/  capabilities; int /*<<< orphan*/  key_mgmt; int /*<<< orphan*/  group_cipher; int /*<<< orphan*/  pairwise_cipher; int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 void* cipher_type_map (int /*<<< orphan*/ ) ; 
 int wpa_parse_wpa_ie (int /*<<< orphan*/  const*,size_t,struct wpa_ie_data*) ; 

int wpa_parse_wpa_ie_wrapper(const u8 *wpa_ie, size_t wpa_ie_len, wifi_wpa_ie_t *data)
{
    struct wpa_ie_data ie;
    int ret = 0;

    ret = wpa_parse_wpa_ie(wpa_ie, wpa_ie_len, &ie);
    data->proto = ie.proto;
    data->pairwise_cipher = cipher_type_map(ie.pairwise_cipher);
    data->group_cipher = cipher_type_map(ie.group_cipher);
    data->key_mgmt = ie.key_mgmt;
    data->capabilities = ie.capabilities;
    data->pmkid = ie.pmkid;
    data->mgmt_group_cipher = cipher_type_map(ie.mgmt_group_cipher);

    return ret;
}