#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_6__ {int /*<<< orphan*/  pb; int /*<<< orphan*/  metadata; TYPE_1__* priv_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  dv_demux; } ;
typedef  TYPE_1__ RawDVContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_TIMECODE_STR_SIZE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_dict_set (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * av_mallocz (int) ; 
 int avio_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_tell (int /*<<< orphan*/ ) ; 
 int dv_extract_timecode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int dv_read_timecode(AVFormatContext *s) {
    int ret;
    char timecode[AV_TIMECODE_STR_SIZE];
    int64_t pos = avio_tell(s->pb);

    // Read 3 DIF blocks: Header block and 2 Subcode blocks.
    int partial_frame_size = 3 * 80;
    uint8_t *partial_frame = av_mallocz(sizeof(*partial_frame) *
                                        partial_frame_size);

    RawDVContext *c = s->priv_data;
    if (!partial_frame)
        return AVERROR(ENOMEM);

    ret = avio_read(s->pb, partial_frame, partial_frame_size);
    if (ret < 0)
        goto finish;

    if (ret < partial_frame_size) {
        ret = -1;
        goto finish;
    }

    ret = dv_extract_timecode(c->dv_demux, partial_frame, timecode);
    if (ret)
        av_dict_set(&s->metadata, "timecode", timecode, 0);
    else
        av_log(s, AV_LOG_ERROR, "Detected timecode is invalid\n");

finish:
    av_free(partial_frame);
    avio_seek(s->pb, pos, SEEK_SET);
    return ret;
}