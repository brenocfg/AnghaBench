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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_3__ {char* host; char* service; char* proto; char* domain; int type; scalar_t__ unicast; } ;
typedef  TYPE_1__ mdns_out_question_t ;

/* Variables and functions */
 scalar_t__ _mdns_append_fqdn (scalar_t__*,scalar_t__*,char const**,scalar_t__) ; 
 scalar_t__ _mdns_append_u16 (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static uint16_t _mdns_append_question(uint8_t * packet, uint16_t * index, mdns_out_question_t * q)
{
    const char * str[4];
    uint8_t str_index = 0;
    uint8_t part_length;
    if (q->host) {
        str[str_index++] = q->host;
    }
    if (q->service) {
        str[str_index++] = q->service;
    }
    if (q->proto) {
        str[str_index++] = q->proto;
    }
    if (q->domain) {
        str[str_index++] = q->domain;
    }

    part_length = _mdns_append_fqdn(packet, index, str, str_index);
    if (!part_length) {
        return 0;
    }

    part_length += _mdns_append_u16(packet, index, q->type);
    part_length += _mdns_append_u16(packet, index, q->unicast?0x8001:0x0001);
    return part_length;
}