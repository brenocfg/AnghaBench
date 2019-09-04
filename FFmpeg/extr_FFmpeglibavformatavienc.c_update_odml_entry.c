#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_14__ {TYPE_1__* codecpar; TYPE_3__* priv_data; } ;
struct TYPE_13__ {TYPE_7__** streams; TYPE_4__* priv_data; int /*<<< orphan*/ * pb; } ;
struct TYPE_12__ {int riff_id; } ;
struct TYPE_10__ {int master_odml_riff_id_base; int audio_strm_offset; int entry; scalar_t__ indx_start; } ;
struct TYPE_11__ {int audio_strm_length; int sample_requested; TYPE_2__ indexes; } ;
struct TYPE_9__ {scalar_t__ codec_type; } ;
typedef  TYPE_3__ AVIStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_4__ AVIContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 scalar_t__ avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_wl32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wl64 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  ff_parse_specific_params (TYPE_7__*,int*,int*,int*) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void update_odml_entry(AVFormatContext *s, int stream_index, int64_t ix, int size)
{
    AVIOContext *pb = s->pb;
    AVIContext *avi = s->priv_data;
    AVIStream *avist = s->streams[stream_index]->priv_data;
    int64_t pos;
    int au_byterate, au_ssize, au_scale;

    avio_flush(pb);
    pos = avio_tell(pb);

    /* Updating one entry in the AVI OpenDML master index */
    avio_seek(pb, avist->indexes.indx_start - 8, SEEK_SET);
    ffio_wfourcc(pb, "indx");             /* enabling this entry */
    avio_skip(pb, 8);
    avio_wl32(pb, avi->riff_id - avist->indexes.master_odml_riff_id_base);          /* nEntriesInUse */
    avio_skip(pb, 16 * (avi->riff_id - avist->indexes.master_odml_riff_id_base));
    avio_wl64(pb, ix);                    /* qwOffset */
    avio_wl32(pb, size);                  /* dwSize */
    ff_parse_specific_params(s->streams[stream_index], &au_byterate, &au_ssize, &au_scale);
    if (s->streams[stream_index]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO && au_ssize > 0) {
        uint32_t audio_segm_size = (avist->audio_strm_length - avist->indexes.audio_strm_offset);
        if ((audio_segm_size % au_ssize > 0) && !avist->sample_requested) {
            avpriv_request_sample(s, "OpenDML index duration for audio packets with partial frames");
            avist->sample_requested = 1;
        }
        avio_wl32(pb, audio_segm_size / au_ssize);  /* dwDuration (sample count) */
    } else
        avio_wl32(pb, avist->indexes.entry);  /* dwDuration (packet count) */

    avio_seek(pb, pos, SEEK_SET);
}