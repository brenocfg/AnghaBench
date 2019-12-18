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
struct TYPE_5__ {TYPE_1__* internal; } ;
struct TYPE_4__ {int /*<<< orphan*/  raw_packet_buffer_remaining_size; int /*<<< orphan*/  raw_packet_buffer_end; int /*<<< orphan*/  raw_packet_buffer; int /*<<< orphan*/  packet_buffer_end; int /*<<< orphan*/  packet_buffer; int /*<<< orphan*/  parse_queue_end; int /*<<< orphan*/  parse_queue; } ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  RAW_PACKET_BUFFER_SIZE ; 
 int /*<<< orphan*/  ff_packet_list_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flush_packet_queue(AVFormatContext *s)
{
    if (!s->internal)
        return;
    ff_packet_list_free(&s->internal->parse_queue,       &s->internal->parse_queue_end);
    ff_packet_list_free(&s->internal->packet_buffer,     &s->internal->packet_buffer_end);
    ff_packet_list_free(&s->internal->raw_packet_buffer, &s->internal->raw_packet_buffer_end);

    s->internal->raw_packet_buffer_remaining_size = RAW_PACKET_BUFFER_SIZE;
}