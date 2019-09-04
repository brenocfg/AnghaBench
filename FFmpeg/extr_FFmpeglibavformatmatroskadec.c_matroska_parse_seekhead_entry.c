#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  void* uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_9__ {int /*<<< orphan*/  pb; } ;
struct TYPE_8__ {scalar_t__ segment_start; size_t num_levels; void* current_id; void* level_up; TYPE_6__* ctx; TYPE_1__* levels; } ;
struct TYPE_7__ {scalar_t__ length; scalar_t__ start; } ;
typedef  TYPE_1__ MatroskaLevel ;
typedef  TYPE_2__ MatroskaDemuxContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 size_t EBML_MAX_DEPTH ; 
 scalar_t__ EBML_UNKNOWN_LENGTH ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,size_t) ; 
 scalar_t__ avio_seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ ) ; 
 int ebml_parse (TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  matroska_segment ; 

__attribute__((used)) static int matroska_parse_seekhead_entry(MatroskaDemuxContext *matroska,
                                         uint64_t pos)
{
    uint32_t level_up       = matroska->level_up;
    uint32_t saved_id       = matroska->current_id;
    int64_t before_pos = avio_tell(matroska->ctx->pb);
    MatroskaLevel level;
    int64_t offset;
    int ret = 0;

    /* seek */
    offset = pos + matroska->segment_start;
    if (avio_seek(matroska->ctx->pb, offset, SEEK_SET) == offset) {
        /* We don't want to lose our seekhead level, so we add
         * a dummy. This is a crude hack. */
        if (matroska->num_levels == EBML_MAX_DEPTH) {
            av_log(matroska->ctx, AV_LOG_INFO,
                   "Max EBML element depth (%d) reached, "
                   "cannot parse further.\n", EBML_MAX_DEPTH);
            ret = AVERROR_INVALIDDATA;
        } else {
            level.start  = 0;
            level.length = EBML_UNKNOWN_LENGTH;
            matroska->levels[matroska->num_levels] = level;
            matroska->num_levels++;
            matroska->current_id                   = 0;

            ret = ebml_parse(matroska, matroska_segment, matroska);

            /* remove dummy level */
            while (matroska->num_levels) {
                uint64_t length = matroska->levels[--matroska->num_levels].length;
                if (length == EBML_UNKNOWN_LENGTH)
                    break;
            }
        }
    }
    /* seek back */
    avio_seek(matroska->ctx->pb, before_pos, SEEK_SET);
    matroska->level_up   = level_up;
    matroska->current_id = saved_id;

    return ret;
}