#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_10__ {scalar_t__ eof_reached; } ;
struct TYPE_9__ {int num_levels; TYPE_1__* ctx; scalar_t__ is_live; scalar_t__ current_id; TYPE_2__* levels; } ;
struct TYPE_8__ {scalar_t__ start; scalar_t__ length; } ;
struct TYPE_7__ {TYPE_4__* pb; } ;
typedef  TYPE_2__ MatroskaLevel ;
typedef  TYPE_3__ MatroskaDemuxContext ;
typedef  TYPE_4__ AVIOContext ;

/* Variables and functions */
 scalar_t__ avio_tell (TYPE_4__*) ; 

__attribute__((used)) static int ebml_level_end(MatroskaDemuxContext *matroska)
{
    AVIOContext *pb = matroska->ctx->pb;
    int64_t pos = avio_tell(pb);

    if (matroska->num_levels > 0) {
        MatroskaLevel *level = &matroska->levels[matroska->num_levels - 1];
        if (pos - level->start >= level->length || matroska->current_id) {
            matroska->num_levels--;
            return 1;
        }
    }
    return (matroska->is_live && matroska->ctx->pb->eof_reached) ? 1 : 0;
}