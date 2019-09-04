#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_8__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {size_t stream_index; } ;
struct TYPE_14__ {TYPE_1__** streams; TYPE_4__* priv_data; } ;
struct TYPE_13__ {TYPE_3__* page_list; } ;
struct TYPE_12__ {struct TYPE_12__* next; TYPE_8__ page; } ;
struct TYPE_11__ {int page_count; } ;
struct TYPE_10__ {TYPE_2__* priv_data; } ;
typedef  TYPE_2__ OGGStreamContext ;
typedef  TYPE_3__ OGGPageList ;
typedef  TYPE_4__ OGGContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_3__**) ; 
 int /*<<< orphan*/  ogg_write_page (TYPE_5__*,TYPE_8__*,int) ; 

__attribute__((used)) static void ogg_write_pages(AVFormatContext *s, int flush)
{
    OGGContext *ogg = s->priv_data;
    OGGPageList *next, *p;

    if (!ogg->page_list)
        return;

    for (p = ogg->page_list; p; ) {
        OGGStreamContext *oggstream =
            s->streams[p->page.stream_index]->priv_data;
        if (oggstream->page_count < 2 && !flush)
            break;
        ogg_write_page(s, &p->page,
                       flush == 1 && oggstream->page_count == 1 ? 4 : 0); // eos
        next = p->next;
        av_freep(&p);
        p = next;
    }
    ogg->page_list = p;
}