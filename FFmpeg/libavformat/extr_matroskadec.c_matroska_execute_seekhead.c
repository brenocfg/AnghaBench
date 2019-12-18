#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_16__ {int nb_elem; TYPE_3__* elem; } ;
struct TYPE_15__ {int cues_parsing_deferred; scalar_t__ segment_start; TYPE_2__* ctx; TYPE_6__ seekhead; } ;
struct TYPE_14__ {int parsed; scalar_t__ pos; } ;
struct TYPE_13__ {scalar_t__ id; scalar_t__ pos; } ;
struct TYPE_12__ {TYPE_1__* pb; } ;
struct TYPE_11__ {int seekable; } ;
typedef  TYPE_3__ MatroskaSeekhead ;
typedef  TYPE_4__ MatroskaLevel1Element ;
typedef  TYPE_5__ MatroskaDemuxContext ;
typedef  TYPE_6__ EbmlList ;

/* Variables and functions */
 int AVIO_SEEKABLE_NORMAL ; 
 scalar_t__ MATROSKA_ID_CUES ; 
 TYPE_4__* matroska_find_level1_elem (TYPE_5__*,scalar_t__) ; 
 scalar_t__ matroska_parse_seekhead_entry (TYPE_5__*,scalar_t__) ; 

__attribute__((used)) static void matroska_execute_seekhead(MatroskaDemuxContext *matroska)
{
    EbmlList *seekhead_list = &matroska->seekhead;
    int i;

    // we should not do any seeking in the streaming case
    if (!(matroska->ctx->pb->seekable & AVIO_SEEKABLE_NORMAL))
        return;

    for (i = 0; i < seekhead_list->nb_elem; i++) {
        MatroskaSeekhead *seekheads = seekhead_list->elem;
        uint32_t id = seekheads[i].id;
        int64_t pos = seekheads[i].pos + matroska->segment_start;

        MatroskaLevel1Element *elem = matroska_find_level1_elem(matroska, id);
        if (!elem || elem->parsed)
            continue;

        elem->pos = pos;

        // defer cues parsing until we actually need cue data.
        if (id == MATROSKA_ID_CUES)
            continue;

        if (matroska_parse_seekhead_entry(matroska, pos) < 0) {
            // mark index as broken
            matroska->cues_parsing_deferred = -1;
            break;
        }

        elem->parsed = 1;
    }
}