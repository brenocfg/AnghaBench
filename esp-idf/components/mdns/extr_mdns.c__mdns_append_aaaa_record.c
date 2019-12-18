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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {char* hostname; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDNS_ANSWER_AAAA ; 
 scalar_t__ MDNS_ANSWER_AAAA_SIZE ; 
 int /*<<< orphan*/  MDNS_ANSWER_AAAA_TTL ; 
 char* MDNS_DEFAULT_DOMAIN ; 
 scalar_t__ MDNS_MAX_PACKET_SIZE ; 
 scalar_t__ _mdns_append_fqdn (scalar_t__*,scalar_t__*,char const**,int) ; 
 scalar_t__ _mdns_append_type (scalar_t__*,scalar_t__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* _mdns_server ; 
 int /*<<< orphan*/  _mdns_set_u16 (scalar_t__*,scalar_t__,scalar_t__) ; 
 scalar_t__ _str_null_or_empty (char const*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,scalar_t__) ; 

__attribute__((used)) static uint16_t _mdns_append_aaaa_record(uint8_t * packet, uint16_t * index, uint8_t * ipv6, bool flush, bool bye)
{
    const char * str[2];
    uint16_t record_length = 0;
    uint8_t part_length;

    str[0] = _mdns_server->hostname;
    str[1] = MDNS_DEFAULT_DOMAIN;

    if (_str_null_or_empty(str[0])) {
        return 0;
    }


    part_length = _mdns_append_fqdn(packet, index, str, 2);
    if (!part_length) {
        return 0;
    }
    record_length += part_length;

    part_length = _mdns_append_type(packet, index, MDNS_ANSWER_AAAA, flush, bye?0:MDNS_ANSWER_AAAA_TTL);
    if (!part_length) {
        return 0;
    }
    record_length += part_length;

    uint16_t data_len_location = *index - 2;

    if ((*index + MDNS_ANSWER_AAAA_SIZE) > MDNS_MAX_PACKET_SIZE) {
        return 0;
    }

    part_length = MDNS_ANSWER_AAAA_SIZE;
    memcpy(packet + *index, ipv6, part_length);
    *index += part_length;
    _mdns_set_u16(packet, data_len_location, part_length);
    record_length += part_length;
    return record_length;
}