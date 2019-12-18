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
struct TYPE_5__ {scalar_t__ size; } ;
struct TYPE_4__ {int pos; TYPE_2__* packet; } ;
typedef  TYPE_1__ PacketWriter ;
typedef  scalar_t__ OPJ_OFF_T ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;
typedef  TYPE_2__ AVPacket ;

/* Variables and functions */
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 scalar_t__ INT_MAX ; 
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 scalar_t__ av_grow_packet (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static OPJ_BOOL stream_seek(OPJ_OFF_T nb_bytes, void *user_data)
{
    PacketWriter *writer = user_data;
    AVPacket *packet = writer->packet;
    if (nb_bytes < 0) {
        return OPJ_FALSE;
    }
    if (nb_bytes > packet->size) {
        if (nb_bytes > INT_MAX - AV_INPUT_BUFFER_PADDING_SIZE ||
            av_grow_packet(packet, (int)nb_bytes - packet->size)) {
            return OPJ_FALSE;
        }
    }
    writer->pos = (int)nb_bytes;
    return OPJ_TRUE;
}