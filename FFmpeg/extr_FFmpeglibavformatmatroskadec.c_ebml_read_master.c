#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_6__ {scalar_t__ num_levels; TYPE_1__* levels; TYPE_4__* ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  length; int /*<<< orphan*/  start; } ;
typedef  TYPE_1__ MatroskaLevel ;
typedef  TYPE_2__ MatroskaDemuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ EBML_MAX_DEPTH ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ebml_read_master(MatroskaDemuxContext *matroska, uint64_t length)
{
    AVIOContext *pb = matroska->ctx->pb;
    MatroskaLevel *level;

    if (matroska->num_levels >= EBML_MAX_DEPTH) {
        av_log(matroska->ctx, AV_LOG_ERROR,
               "File moves beyond max. allowed depth (%d)\n", EBML_MAX_DEPTH);
        return AVERROR(ENOSYS);
    }

    level         = &matroska->levels[matroska->num_levels++];
    level->start  = avio_tell(pb);
    level->length = length;

    return 0;
}