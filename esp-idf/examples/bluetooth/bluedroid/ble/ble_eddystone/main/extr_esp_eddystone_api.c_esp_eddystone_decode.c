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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  int esp_err_t ;
struct TYPE_5__ {scalar_t__ srv_data_type; scalar_t__ flags; scalar_t__ frame_type; scalar_t__ srv_uuid; } ;
struct TYPE_6__ {TYPE_1__ common; } ;
typedef  TYPE_2__ esp_eddystone_result_t ;

/* Variables and functions */
 scalar_t__ EDDYSTONE_FRAME_TYPE_TLM ; 
 scalar_t__ EDDYSTONE_FRAME_TYPE_UID ; 
 scalar_t__ EDDYSTONE_FRAME_TYPE_URL ; 
 scalar_t__ EDDYSTONE_SERVICE_UUID ; 
#define  ESP_BLE_AD_TYPE_16SRV_CMPL 130 
#define  ESP_BLE_AD_TYPE_FLAG 129 
#define  ESP_BLE_AD_TYPE_SERVICE_DATA 128 
 int esp_eddystone_get_inform (scalar_t__ const*,scalar_t__,TYPE_2__*) ; 
 scalar_t__ little_endian_read_16 (scalar_t__ const*,scalar_t__) ; 

esp_err_t esp_eddystone_decode(const uint8_t* buf, uint8_t len, esp_eddystone_result_t* res)
{
    if (len == 0 || buf == NULL || res == NULL) {
        return -1;
    }
    uint8_t pos=0;
    while(res->common.srv_data_type != EDDYSTONE_SERVICE_UUID) 
    {
        pos++;
        if(pos >= len ) { 
            return -1;
        }
        uint8_t ad_type = buf[pos++];
        switch(ad_type) 
        {
            case ESP_BLE_AD_TYPE_FLAG: {
                res->common.flags = buf[pos++];
                break;
            }
            case ESP_BLE_AD_TYPE_16SRV_CMPL: {
                uint16_t uuid = little_endian_read_16(buf, pos);
                if(uuid != EDDYSTONE_SERVICE_UUID) {
                    return -1; 
                }
                res->common.srv_uuid = uuid;
                pos += 2;
                break;
            }
            case ESP_BLE_AD_TYPE_SERVICE_DATA: {
                uint16_t type = little_endian_read_16(buf, pos);
                pos += 2;
                uint8_t frame_type = buf[pos++];
                if(type != EDDYSTONE_SERVICE_UUID || !(frame_type == EDDYSTONE_FRAME_TYPE_UID || frame_type == EDDYSTONE_FRAME_TYPE_URL || 
                   frame_type == EDDYSTONE_FRAME_TYPE_TLM)) {
                    return -1;
                }
                res->common.srv_data_type = type;
                res->common.frame_type = frame_type;
                break;
            }
            default:
                break;
        }
    }
    return esp_eddystone_get_inform(buf+pos, len-pos, res);
}