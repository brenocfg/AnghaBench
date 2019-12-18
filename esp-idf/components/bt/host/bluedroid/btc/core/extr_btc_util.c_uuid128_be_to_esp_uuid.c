#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int* uuid128; int uuid16; int uuid32; } ;
struct TYPE_5__ {int len; TYPE_1__ uuid; } ;
typedef  TYPE_2__ esp_bt_uuid_t ;

/* Variables and functions */
 int ESP_UUID_LEN_128 ; 
 scalar_t__ base_uuid_be ; 
 scalar_t__ memcmp (scalar_t__,int*,int) ; 

void uuid128_be_to_esp_uuid(esp_bt_uuid_t *u, uint8_t* uuid128)
{
    if (memcmp(base_uuid_be+4, uuid128 + 4, 12) != 0) {
        u->len = ESP_UUID_LEN_128;
        uint8_t *p_i = uuid128 + ESP_UUID_LEN_128 - 1;
        uint8_t *p_o = u->uuid.uuid128;
        uint8_t *p_end = p_o + ESP_UUID_LEN_128;
        for (; p_o != p_end; *p_o++ = *p_i--)
            ;
    } else if (uuid128[0] == 0 && uuid128[1] == 0) {
        u->len = 2;
        u->uuid.uuid16 = (uuid128[2] << 8) + uuid128[3];
    } else {
        u->len = 4;
        u->uuid.uuid32 = (uuid128[2] << 8) + uuid128[3];
        u->uuid.uuid32 += (uuid128[0] << 24) + (uuid128[1] << 16);
    }

    return;
}