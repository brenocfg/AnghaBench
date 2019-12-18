#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int nb_streams; int /*<<< orphan*/ ** streams; } ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int MP4DecConfigDescrTag ; 
 int MP4ESDescrTag ; 
 int /*<<< orphan*/  avio_rb16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_rb32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_mp4_parse_es_descr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ff_mp4_read_dec_config_descr (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_mp4_read_descr (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 

int ff_mov_read_esds(AVFormatContext *fc, AVIOContext *pb)
{
    AVStream *st;
    int tag, ret = 0;

    if (fc->nb_streams < 1)
        return 0;
    st = fc->streams[fc->nb_streams-1];

    avio_rb32(pb); /* version + flags */
    ff_mp4_read_descr(fc, pb, &tag);
    if (tag == MP4ESDescrTag) {
        ff_mp4_parse_es_descr(pb, NULL);
    } else
        avio_rb16(pb); /* ID */

    ff_mp4_read_descr(fc, pb, &tag);
    if (tag == MP4DecConfigDescrTag)
        ret = ff_mp4_read_dec_config_descr(fc, st, pb);

    return ret;
}