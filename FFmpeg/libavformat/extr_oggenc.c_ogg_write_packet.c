#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int nb_streams; TYPE_1__** streams; } ;
struct TYPE_11__ {scalar_t__ segments_count; } ;
struct TYPE_12__ {TYPE_2__ page; } ;
struct TYPE_10__ {TYPE_3__* priv_data; } ;
typedef  TYPE_3__ OGGStreamContext ;
typedef  int /*<<< orphan*/  AVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  ogg_buffer_page (TYPE_4__*,TYPE_3__*) ; 
 int ogg_write_packet_internal (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_write_pages (TYPE_4__*,int) ; 

__attribute__((used)) static int ogg_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    int i;

    if (pkt)
        return ogg_write_packet_internal(s, pkt);

    for (i = 0; i < s->nb_streams; i++) {
        OGGStreamContext *oggstream = s->streams[i]->priv_data;
        if (oggstream->page.segments_count)
            ogg_buffer_page(s, oggstream);
    }

    ogg_write_pages(s, 2);
    return 1;
}