#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_24__ {scalar_t__ codec_type; scalar_t__ codec_id; } ;
struct TYPE_23__ {int nb_streams; TYPE_1__** streams; TYPE_3__* pb; TYPE_4__* priv_data; } ;
struct TYPE_22__ {int riff_id; int master_index_max_size; scalar_t__ odml_list; int /*<<< orphan*/  riff_start; int /*<<< orphan*/  movi_list; } ;
struct TYPE_21__ {int seekable; } ;
struct TYPE_20__ {int packet_count; int max_size; scalar_t__ frames_hdr_strm; int /*<<< orphan*/  last_dts; } ;
struct TYPE_19__ {TYPE_2__* priv_data; TYPE_6__* codecpar; } ;
typedef  TYPE_2__ AVIStream ;
typedef  TYPE_3__ AVIOContext ;
typedef  TYPE_4__ AVIContext ;
typedef  TYPE_5__ AVFormatContext ;
typedef  TYPE_6__ AVCodecParameters ;

/* Variables and functions */
 int AVIO_SEEKABLE_NORMAL ; 
 int AVI_MASTER_INDEX_ENTRY_SIZE ; 
 int AVI_MASTER_INDEX_PREFIX_SIZE ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_MP2 ; 
 scalar_t__ AV_CODEC_ID_MP3 ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  avi_write_counters (TYPE_5__*,int) ; 
 int avi_write_idx1 (TYPE_5__*) ; 
 int /*<<< orphan*/  avi_write_ix (TYPE_5__*) ; 
 int /*<<< orphan*/  avio_seek (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (TYPE_3__*,int) ; 
 scalar_t__ avio_tell (TYPE_3__*) ; 
 int /*<<< orphan*/  avio_wl32 (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ff_end_tag (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffio_wfourcc (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  write_skip_frames (TYPE_5__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int avi_write_trailer(AVFormatContext *s)
{
    AVIContext *avi = s->priv_data;
    AVIOContext *pb = s->pb;
    int res = 0;
    int i, n, nb_frames;
    int64_t file_size;

    for (i = 0; i < s->nb_streams; i++) {
        AVIStream *avist = s->streams[i]->priv_data;
        write_skip_frames(s, i, avist->last_dts);
    }

    if (pb->seekable & AVIO_SEEKABLE_NORMAL) {
        if (avi->riff_id == 1) {
            ff_end_tag(pb, avi->movi_list);
            res = avi_write_idx1(s);
            ff_end_tag(pb, avi->riff_start);
        } else {
            avi_write_ix(s);
            ff_end_tag(pb, avi->movi_list);
            ff_end_tag(pb, avi->riff_start);

            file_size = avio_tell(pb);
            avio_seek(pb, avi->odml_list - 8, SEEK_SET);
            ffio_wfourcc(pb, "LIST"); /* Making this AVI OpenDML one */
            avio_skip(pb, 16);

            for (n = nb_frames = 0; n < s->nb_streams; n++) {
                AVCodecParameters *par = s->streams[n]->codecpar;
                AVIStream *avist       = s->streams[n]->priv_data;

                if (par->codec_type == AVMEDIA_TYPE_VIDEO) {
                    if (nb_frames < avist->packet_count)
                        nb_frames = avist->packet_count;
                } else {
                    if (par->codec_id == AV_CODEC_ID_MP2 ||
                        par->codec_id == AV_CODEC_ID_MP3)
                        nb_frames += avist->packet_count;
                }
            }
            avio_wl32(pb, nb_frames);
            avio_seek(pb, file_size, SEEK_SET);

            avi_write_counters(s, avi->riff_id);
        }
    }

    if (avi->riff_id >= avi->master_index_max_size) {
        int index_space = AVI_MASTER_INDEX_PREFIX_SIZE +
                          AVI_MASTER_INDEX_ENTRY_SIZE * avi->riff_id;
        av_log(s, AV_LOG_WARNING, "Output file not strictly OpenDML compliant, "
               "consider re-muxing with 'reserve_index_space' option value >= %d\n",
               index_space);
    }

    for (i = 0; i < s->nb_streams; i++) {
        AVIStream *avist = s->streams[i]->priv_data;
        if (pb->seekable & AVIO_SEEKABLE_NORMAL) {
            avio_seek(pb, avist->frames_hdr_strm + 4, SEEK_SET);
            avio_wl32(pb, avist->max_size);
        }
    }

    return res;
}