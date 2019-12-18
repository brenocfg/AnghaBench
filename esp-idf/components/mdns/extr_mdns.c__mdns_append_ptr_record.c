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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  MDNS_ANSWER_PTR ; 
 int /*<<< orphan*/  MDNS_ANSWER_PTR_TTL ; 
 char* MDNS_DEFAULT_DOMAIN ; 
 scalar_t__ _mdns_append_fqdn (scalar_t__*,scalar_t__*,char const**,int) ; 
 scalar_t__ _mdns_append_type (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _mdns_set_u16 (scalar_t__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static uint16_t _mdns_append_ptr_record(uint8_t * packet, uint16_t * index, const char * instance, const char * service, const char * proto, bool flush, bool bye)
{
    const char * str[4];
    uint16_t record_length = 0;
    uint8_t part_length;

    if (service == NULL) {
        return 0;
    }

    str[0] = instance;
    str[1] = service;
    str[2] = proto;
    str[3] = MDNS_DEFAULT_DOMAIN;

    part_length = _mdns_append_fqdn(packet, index, str + 1, 3);
    if (!part_length) {
        return 0;
    }
    record_length += part_length;

    part_length = _mdns_append_type(packet, index, MDNS_ANSWER_PTR, false, bye?0:MDNS_ANSWER_PTR_TTL);
    if (!part_length) {
        return 0;
    }
    record_length += part_length;

    uint16_t data_len_location = *index - 2;
    part_length = _mdns_append_fqdn(packet, index, str, 4);
    if (!part_length) {
        return 0;
    }
    _mdns_set_u16(packet, data_len_location, part_length);
    record_length += part_length;
    return record_length;
}