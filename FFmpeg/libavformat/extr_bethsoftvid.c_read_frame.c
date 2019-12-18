#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct TYPE_20__ {TYPE_3__** streams; } ;
struct TYPE_19__ {scalar_t__* data; int pos; size_t stream_index; int duration; int /*<<< orphan*/  flags; } ;
struct TYPE_18__ {size_t index; TYPE_1__* codecpar; } ;
struct TYPE_17__ {size_t video_index; scalar_t__ audio_index; int width; int height; int bethsoft_global_delay; scalar_t__* palette; int /*<<< orphan*/  nframes; int /*<<< orphan*/  sample_rate; } ;
struct TYPE_16__ {int width; int height; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ BVID_DemuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CODEC_ID_BETHSOFTVID ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_DATA_PALETTE ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int BUFFER_PADDING_SIZE ; 
 int BVID_PALETTE_SIZE ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 scalar_t__ VIDEO_I_FRAME ; 
 scalar_t__ VIDEO_YOFF_P_FRAME ; 
 scalar_t__* av_fast_realloc (scalar_t__*,unsigned int*,int) ; 
 int /*<<< orphan*/  av_free (scalar_t__*) ; 
 int /*<<< orphan*/  av_freep (scalar_t__**) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__* av_malloc (unsigned int) ; 
 int av_new_packet (TYPE_4__*,int) ; 
 scalar_t__* av_packet_new_side_data (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 TYPE_3__* avformat_new_stream (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,scalar_t__*,int) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_request_sample (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 

__attribute__((used)) static int read_frame(BVID_DemuxContext *vid, AVIOContext *pb, AVPacket *pkt,
                      uint8_t block_type, AVFormatContext *s)
{
    uint8_t * vidbuf_start = NULL;
    int vidbuf_nbytes = 0;
    int code;
    int bytes_copied = 0;
    int position, duration, npixels;
    unsigned int vidbuf_capacity;
    int ret = 0;
    AVStream *st;

    if (vid->video_index < 0) {
        st = avformat_new_stream(s, NULL);
        if (!st)
            return AVERROR(ENOMEM);
        vid->video_index = st->index;
        if (vid->audio_index < 0) {
            avpriv_request_sample(s, "Using default video time base since "
                                  "having no audio packet before the first "
                                  "video packet");
        }
        avpriv_set_pts_info(st, 64, 185, vid->sample_rate);
        st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
        st->codecpar->codec_id   = AV_CODEC_ID_BETHSOFTVID;
        st->codecpar->width      = vid->width;
        st->codecpar->height     = vid->height;
    }
    st      = s->streams[vid->video_index];
    npixels = st->codecpar->width * st->codecpar->height;

    vidbuf_start = av_malloc(vidbuf_capacity = BUFFER_PADDING_SIZE);
    if(!vidbuf_start)
        return AVERROR(ENOMEM);

    // save the file position for the packet, include block type
    position = avio_tell(pb) - 1;

    vidbuf_start[vidbuf_nbytes++] = block_type;

    // get the current packet duration
    duration = vid->bethsoft_global_delay + avio_rl16(pb);

    // set the y offset if it exists (decoder header data should be in data section)
    if(block_type == VIDEO_YOFF_P_FRAME){
        if (avio_read(pb, &vidbuf_start[vidbuf_nbytes], 2) != 2) {
            ret = AVERROR(EIO);
            goto fail;
        }
        vidbuf_nbytes += 2;
    }

    do{
        vidbuf_start = av_fast_realloc(vidbuf_start, &vidbuf_capacity, vidbuf_nbytes + BUFFER_PADDING_SIZE);
        if(!vidbuf_start)
            return AVERROR(ENOMEM);

        code = avio_r8(pb);
        vidbuf_start[vidbuf_nbytes++] = code;

        if(code >= 0x80){ // rle sequence
            if(block_type == VIDEO_I_FRAME)
                vidbuf_start[vidbuf_nbytes++] = avio_r8(pb);
        } else if(code){ // plain sequence
            if (avio_read(pb, &vidbuf_start[vidbuf_nbytes], code) != code) {
                ret = AVERROR(EIO);
                goto fail;
            }
            vidbuf_nbytes += code;
        }
        bytes_copied += code & 0x7F;
        if(bytes_copied == npixels){ // sometimes no stop character is given, need to keep track of bytes copied
            // may contain a 0 byte even if read all pixels
            if(avio_r8(pb))
                avio_seek(pb, -1, SEEK_CUR);
            break;
        }
        if (bytes_copied > npixels) {
            ret = AVERROR_INVALIDDATA;
            goto fail;
        }
    } while(code);

    // copy data into packet
    if ((ret = av_new_packet(pkt, vidbuf_nbytes)) < 0)
        goto fail;
    memcpy(pkt->data, vidbuf_start, vidbuf_nbytes);

    pkt->pos = position;
    pkt->stream_index = vid->video_index;
    pkt->duration = duration;
    if (block_type == VIDEO_I_FRAME)
        pkt->flags |= AV_PKT_FLAG_KEY;

    /* if there is a new palette available, add it to packet side data */
    if (vid->palette) {
        uint8_t *pdata = av_packet_new_side_data(pkt, AV_PKT_DATA_PALETTE,
                                                 BVID_PALETTE_SIZE);
        if (!pdata) {
            ret = AVERROR(ENOMEM);
            av_log(s, AV_LOG_ERROR, "Failed to allocate palette side data\n");
            goto fail;
        }
        memcpy(pdata, vid->palette, BVID_PALETTE_SIZE);

        av_freep(&vid->palette);
    }

    vid->nframes--;  // used to check if all the frames were read
fail:
    av_free(vidbuf_start);
    return ret;
}