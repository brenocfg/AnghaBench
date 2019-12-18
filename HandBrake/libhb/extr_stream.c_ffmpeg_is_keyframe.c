#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_10__ {int* data; int flags; } ;
struct TYPE_11__ {size_t ffmpeg_video_id; TYPE_4__ ffmpeg_pkt; TYPE_3__* ffmpeg_ic; } ;
typedef  TYPE_5__ hb_stream_t ;
struct TYPE_9__ {TYPE_2__** streams; } ;
struct TYPE_8__ {TYPE_1__* codecpar; } ;
struct TYPE_7__ {int codec_id; int* extradata; } ;

/* Variables and functions */
#define  AV_CODEC_ID_VC1 129 
#define  AV_CODEC_ID_WMV3 128 
 int AV_PKT_FLAG_KEY ; 

__attribute__((used)) static int ffmpeg_is_keyframe( hb_stream_t *stream )
{
    uint8_t *pkt;

    switch (stream->ffmpeg_ic->streams[stream->ffmpeg_video_id]->codecpar->codec_id)
    {
        case AV_CODEC_ID_VC1:
            // XXX the VC1 codec doesn't mark key frames so to get previews
            // we do it ourselves here. The decoder gets messed up if it
            // doesn't get a SEQ header first so we consider that to be a key frame.
            pkt = stream->ffmpeg_pkt.data;
            if ( !pkt[0] && !pkt[1] && pkt[2] == 1 && pkt[3] == 0x0f )
                return 1;

            return 0;

        case AV_CODEC_ID_WMV3:
            // XXX the ffmpeg WMV3 codec doesn't mark key frames.
            // Only M$ could make I-frame detection this complicated: there
            // are two to four bits of unused junk ahead of the frame type
            // so we have to look at the sequence header to find out how much
            // to skip. Then there are three different ways of coding the type
            // depending on whether it's main or advanced profile then whether
            // there are bframes or not so we have to look at the sequence
            // header to get that.
            pkt = stream->ffmpeg_pkt.data;
            uint8_t *seqhdr = stream->ffmpeg_ic->streams[stream->ffmpeg_video_id]->codecpar->extradata;
            int pshift = 2;
            if ( ( seqhdr[3] & 0x02 ) == 0 )
                // no FINTERPFLAG
                ++pshift;
            if ( ( seqhdr[3] & 0x80 ) == 0 )
                // no RANGEREDUCTION
                ++pshift;
            if ( seqhdr[3] & 0x70 )
                // stream has b-frames
                return ( ( pkt[0] >> pshift ) & 0x3 ) == 0x01;

            return ( ( pkt[0] >> pshift ) & 0x2 ) == 0;

        default:
            break;
    }
    return ( stream->ffmpeg_pkt.flags & AV_PKT_FLAG_KEY );
}