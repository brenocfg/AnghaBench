#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
typedef  scalar_t__ int8_t ;
typedef  int esp_err_t ;
struct TYPE_5__ {scalar_t__ version; void* time; void* adv_count; scalar_t__ temperature; void* battery_voltage; } ;
struct TYPE_6__ {TYPE_1__ tlm; } ;
struct TYPE_7__ {TYPE_2__ inform; } ;
typedef  TYPE_3__ esp_eddystone_result_t ;

/* Variables and functions */
 scalar_t__ EDDYSTONE_TLM_DATA_LEN ; 
 void* big_endian_read_16 (scalar_t__ const*,scalar_t__) ; 
 void* big_endian_read_32 (scalar_t__ const*,scalar_t__) ; 

__attribute__((used)) static esp_err_t esp_eddystone_tlm_received(const uint8_t* buf, uint8_t len, esp_eddystone_result_t* res)
{
    uint8_t pos = 0;
    if(len > EDDYSTONE_TLM_DATA_LEN) {
        //ERROR:TLM too long
        return -1;
    }
    res->inform.tlm.version = buf[pos++];
    res->inform.tlm.battery_voltage = big_endian_read_16(buf, pos);
    pos += 2;
    uint16_t temp = big_endian_read_16(buf, pos);
    int8_t temp_integral = (int8_t)((temp >> 8) & 0xff);
    float temp_decimal = (temp & 0xff) / 256.0;
    res->inform.tlm.temperature = temp_integral + temp_decimal;
    pos += 2;
    res->inform.tlm.adv_count = big_endian_read_32(buf, pos);
    pos += 4;
    res->inform.tlm.time = big_endian_read_32(buf, pos);
    return 0;
}