#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_2__ {scalar_t__ key_len; scalar_t__* key; } ;

/* Variables and functions */
 int ESP_FAIL ; 
 int ESP_OK ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 TYPE_1__* gWpsSm ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int,int) ; 
 int /*<<< orphan*/  os_free (scalar_t__*) ; 
 scalar_t__ os_zalloc (scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__*) ; 

int
wps_key_save(char *key, u8 key_len)
{
    u8 *tmpkey;

    if (!key || !gWpsSm) {
        return ESP_FAIL;
    }

    memset(gWpsSm->key, 0x00, sizeof(gWpsSm->key));
    memcpy(gWpsSm->key, key, key_len);
    gWpsSm->key_len = key_len;

    tmpkey = (u8 *)os_zalloc(key_len + 1);
    if (tmpkey) {
        memcpy(tmpkey, key, key_len);
        wpa_printf(MSG_DEBUG, "WPS: key[%s]", tmpkey);
        os_free(tmpkey);
    }
    return ESP_OK;
}