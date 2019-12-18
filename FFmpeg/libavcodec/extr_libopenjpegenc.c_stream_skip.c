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
struct TYPE_5__ {int size; } ;
struct TYPE_4__ {scalar_t__ pos; TYPE_2__* packet; } ;
typedef  TYPE_1__ PacketWriter ;
typedef  scalar_t__ OPJ_SIZE_T ;
typedef  scalar_t__ OPJ_OFF_T ;
typedef  TYPE_2__ AVPacket ;

/* Variables and functions */
 int AV_INPUT_BUFFER_PADDING_SIZE ; 
 int INT_MAX ; 
 scalar_t__ av_grow_packet (TYPE_2__*,int) ; 

__attribute__((used)) static OPJ_OFF_T stream_skip(OPJ_OFF_T nb_bytes, void *user_data)
{
    PacketWriter *writer = user_data;
    AVPacket *packet = writer->packet;
    if (nb_bytes < 0) {
        if (writer->pos == 0) {
            return (OPJ_SIZE_T)-1;
        }
        if (nb_bytes + writer->pos < 0) {
            nb_bytes = -writer->pos;
        }
    } else {
        int remaining = packet->size - writer->pos;
        if (nb_bytes > remaining) {
            OPJ_SIZE_T needed = nb_bytes - remaining;
            int max_growth = INT_MAX - AV_INPUT_BUFFER_PADDING_SIZE - packet->size;
            if (needed > max_growth) {
                return (OPJ_SIZE_T)-1;
            }
            if (av_grow_packet(packet, (int)needed)) {
                return (OPJ_SIZE_T)-1;
            }
        }
    }
    writer->pos += (int)nb_bytes;
    return nb_bytes;
}