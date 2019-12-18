#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int nb_streams; TYPE_3__** streams; } ;
struct TYPE_13__ {TYPE_2__* priv_data; } ;
struct TYPE_11__ {int flags; int /*<<< orphan*/  start_granule; } ;
struct TYPE_12__ {TYPE_1__ page; int /*<<< orphan*/ * header_len; int /*<<< orphan*/ * header; } ;
typedef  TYPE_2__ OGGStreamContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  ogg_buffer_data (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ogg_buffer_page (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ogg_write_pages (TYPE_4__*,int) ; 

__attribute__((used)) static int ogg_write_header(AVFormatContext *s)
{
    OGGStreamContext *oggstream = NULL;
    int i, j;

    for (j = 0; j < s->nb_streams; j++) {
        oggstream = s->streams[j]->priv_data;
        ogg_buffer_data(s, s->streams[j], oggstream->header[0],
                        oggstream->header_len[0], 0, 1);
        oggstream->page.flags |= 2; // bos
        ogg_buffer_page(s, oggstream);
    }
    for (j = 0; j < s->nb_streams; j++) {
        AVStream *st = s->streams[j];
        oggstream = st->priv_data;
        for (i = 1; i < 3; i++) {
            if (oggstream->header_len[i])
                ogg_buffer_data(s, st, oggstream->header[i],
                                oggstream->header_len[i], 0, 1);
        }
        ogg_buffer_page(s, oggstream);
    }

    oggstream->page.start_granule = AV_NOPTS_VALUE;

    ogg_write_pages(s, 2);

    return 0;
}