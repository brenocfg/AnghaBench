#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * buffer; } ;
struct TYPE_7__ {int type; int size; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ QDM2SubPacket ;
typedef  TYPE_2__ GetBitContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int get_bits (TYPE_2__*,int) ; 
 int get_bits_count (TYPE_2__*) ; 

__attribute__((used)) static void qdm2_decode_sub_packet_header(GetBitContext *gb,
                                          QDM2SubPacket *sub_packet)
{
    sub_packet->type = get_bits(gb, 8);

    if (sub_packet->type == 0) {
        sub_packet->size = 0;
        sub_packet->data = NULL;
    } else {
        sub_packet->size = get_bits(gb, 8);

        if (sub_packet->type & 0x80) {
            sub_packet->size <<= 8;
            sub_packet->size  |= get_bits(gb, 8);
            sub_packet->type  &= 0x7f;
        }

        if (sub_packet->type == 0x7f)
            sub_packet->type |= (get_bits(gb, 8) << 8);

        // FIXME: this depends on bitreader-internal data
        sub_packet->data = &gb->buffer[get_bits_count(gb) / 8];
    }

    av_log(NULL, AV_LOG_DEBUG, "Subpacket: type=%d size=%d start_offs=%x\n",
           sub_packet->type, sub_packet->size, get_bits_count(gb) / 8);
}