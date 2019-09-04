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
typedef  int uint32_t ;
typedef  int int64_t ;
struct TYPE_5__ {int current_id; int done; scalar_t__ num_levels; TYPE_1__* ctx; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pb; } ;
typedef  TYPE_2__ MatroskaDemuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int MATROSKA_ID_ATTACHMENTS ; 
 int MATROSKA_ID_CHAPTERS ; 
 int MATROSKA_ID_CLUSTER ; 
 int MATROSKA_ID_CUES ; 
 int MATROSKA_ID_INFO ; 
 int MATROSKA_ID_SEEKHEAD ; 
 int MATROSKA_ID_TAGS ; 
 int MATROSKA_ID_TRACKS ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_feof (int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_rb32 (int /*<<< orphan*/ *) ; 
 int avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int matroska_resync(MatroskaDemuxContext *matroska, int64_t last_pos)
{
    AVIOContext *pb = matroska->ctx->pb;
    int64_t ret;
    uint32_t id;
    matroska->current_id = 0;
    matroska->num_levels = 0;

    /* seek to next position to resync from */
    if ((ret = avio_seek(pb, last_pos + 1, SEEK_SET)) < 0) {
        matroska->done = 1;
        return ret;
    }

    id = avio_rb32(pb);

    // try to find a toplevel element
    while (!avio_feof(pb)) {
        if (id == MATROSKA_ID_INFO     || id == MATROSKA_ID_TRACKS      ||
            id == MATROSKA_ID_CUES     || id == MATROSKA_ID_TAGS        ||
            id == MATROSKA_ID_SEEKHEAD || id == MATROSKA_ID_ATTACHMENTS ||
            id == MATROSKA_ID_CLUSTER  || id == MATROSKA_ID_CHAPTERS) {
            matroska->current_id = id;
            return 0;
        }
        id = (id << 8) | avio_r8(pb);
    }

    matroska->done = 1;
    return AVERROR_EOF;
}