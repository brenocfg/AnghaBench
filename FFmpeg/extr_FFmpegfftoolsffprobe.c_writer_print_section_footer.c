#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {size_t level; TYPE_1__* writer; int /*<<< orphan*/  nb_section_frame; int /*<<< orphan*/  nb_section_packet; int /*<<< orphan*/ * nb_item; TYPE_2__** section; } ;
typedef  TYPE_3__ WriterContext ;
struct TYPE_7__ {int id; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* print_section_footer ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int SECTION_ID_NONE ; 
 int SECTION_ID_PACKET ; 
 int SECTION_ID_PACKETS_AND_FRAMES ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static inline void writer_print_section_footer(WriterContext *wctx)
{
    int section_id = wctx->section[wctx->level]->id;
    int parent_section_id = wctx->level ?
        wctx->section[wctx->level-1]->id : SECTION_ID_NONE;

    if (parent_section_id != SECTION_ID_NONE)
        wctx->nb_item[wctx->level-1]++;
    if (parent_section_id == SECTION_ID_PACKETS_AND_FRAMES) {
        if (section_id == SECTION_ID_PACKET) wctx->nb_section_packet++;
        else                                     wctx->nb_section_frame++;
    }
    if (wctx->writer->print_section_footer)
        wctx->writer->print_section_footer(wctx);
    wctx->level--;
}