#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_11__ {int nb_streams; TYPE_3__** streams; } ;
struct TYPE_10__ {int /*<<< orphan*/  codecpar; } ;
struct TYPE_9__ {int size; } ;
struct TYPE_8__ {TYPE_6__* fc; } ;
typedef  TYPE_1__ MOVContext ;
typedef  TYPE_2__ MOVAtom ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int FLAC_METADATA_TYPE_STREAMINFO ; 
 int FLAC_STREAMINFO_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ avio_r8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb24 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int ff_get_extradata (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  flac_parse_block_header (int /*<<< orphan*/ *,int*,int*,int*) ; 

__attribute__((used)) static int mov_read_dfla(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    AVStream *st;
    int last, type, size, ret;
    uint8_t buf[4];

    if (c->fc->nb_streams < 1)
        return 0;
    st = c->fc->streams[c->fc->nb_streams-1];

    if ((uint64_t)atom.size > (1<<30) || atom.size < 42)
        return AVERROR_INVALIDDATA;

    /* Check FlacSpecificBox version. */
    if (avio_r8(pb) != 0)
        return AVERROR_INVALIDDATA;

    avio_rb24(pb); /* Flags */

    avio_read(pb, buf, sizeof(buf));
    flac_parse_block_header(buf, &last, &type, &size);

    if (type != FLAC_METADATA_TYPE_STREAMINFO || size != FLAC_STREAMINFO_SIZE) {
        av_log(c->fc, AV_LOG_ERROR, "STREAMINFO must be first FLACMetadataBlock\n");
        return AVERROR_INVALIDDATA;
    }

    ret = ff_get_extradata(c->fc, st->codecpar, pb, size);
    if (ret < 0)
        return ret;

    if (!last)
        av_log(c->fc, AV_LOG_WARNING, "non-STREAMINFO FLACMetadataBlock(s) ignored\n");

    return 0;
}