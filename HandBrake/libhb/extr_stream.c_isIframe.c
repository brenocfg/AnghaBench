#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {TYPE_3__* list; } ;
struct TYPE_7__ {TYPE_1__ pes; } ;
typedef  TYPE_2__ hb_stream_t ;
struct TYPE_8__ {int stream_type; scalar_t__ codec_param; } ;
typedef  TYPE_3__ hb_pes_stream_t ;

/* Variables and functions */
 scalar_t__ AV_CODEC_ID_H264 ; 
 scalar_t__ AV_CODEC_ID_MPEG1VIDEO ; 
 scalar_t__ AV_CODEC_ID_MPEG2VIDEO ; 
 scalar_t__ AV_CODEC_ID_MPEG4 ; 
 scalar_t__ AV_CODEC_ID_VC1 ; 
 int isRecoveryPoint (int const*,int) ; 
 int pes_index_of_video (TYPE_2__*) ; 

__attribute__((used)) static int isIframe( hb_stream_t *stream, const uint8_t *buf, int len )
{
    // For mpeg2: look for a gop start or i-frame picture start
    // for h.264: look for idr nal type or a slice header for an i-frame
    // for vc1:   look for a Sequence header
    int ii;
    uint32_t strid = 0;


    int vid = pes_index_of_video( stream );
    hb_pes_stream_t *pes = &stream->pes.list[vid];
    if ( pes->stream_type <= 2 ||
         pes->codec_param == AV_CODEC_ID_MPEG1VIDEO ||
         pes->codec_param == AV_CODEC_ID_MPEG2VIDEO )
    {
        // This section of the code handles MPEG-1 and MPEG-2 video streams
        for (ii = 0; ii < len; ii++)
        {
            strid = (strid << 8) | buf[ii];
            if ( ( strid >> 8 ) == 1 )
            {
                // we found a start code
                uint8_t id = strid;
                switch ( id )
                {
                    case 0xB8: // group_start_code (GOP header)
                    case 0xB3: // sequence_header code
                        return 1;

                    case 0x00: // picture_start_code
                        // picture_header, let's see if it's an I-frame
                        if (ii < len - 3)
                        {
                            // check if picture_coding_type == 1
                            if ((buf[ii+2] & (0x7 << 3)) == (1 << 3))
                            {
                                // found an I-frame picture
                                return 1;
                            }
                        }
                        break;
                }
            }
        }
        // didn't find an I-frame
        return 0;
    }
    if ( pes->stream_type == 0x1b || pes->codec_param == AV_CODEC_ID_H264 )
    {
        // we have an h.264 stream
        for (ii = 0; ii < len; ii++)
        {
            strid = (strid << 8) | buf[ii];
            if ( ( strid >> 8 ) == 1 )
            {
                // we found a start code - remove the ref_idc from the nal type
                uint8_t nal_type = strid & 0x1f;
                if ( nal_type == 0x01 )
                {
                    // Found slice and no recovery point
                    return 0;
                }
                if ( nal_type == 0x05 )
                {
                    // h.264 IDR picture start
                    return 1;
                }
                else if ( nal_type == 0x06 )
                {
                    int off = ii + 1;
                    int recovery_frames = isRecoveryPoint( buf+off, len-off );
                    if ( recovery_frames )
                    {
                        return recovery_frames;
                    }
                }
            }
        }
        // didn't find an I-frame
        return 0;
    }
    if ( pes->stream_type == 0xea || pes->codec_param == AV_CODEC_ID_VC1 )
    {
        // we have an vc1 stream
        for (ii = 0; ii < len; ii++)
        {
            strid = (strid << 8) | buf[ii];
            if ( strid == 0x10f )
            {
                // the ffmpeg vc1 decoder requires a seq hdr code in the first
                // frame.
                return 1;
            }
        }
        // didn't find an I-frame
        return 0;
    }
    if ( pes->stream_type == 0x10 || pes->codec_param == AV_CODEC_ID_MPEG4 )
    {
        // we have an mpeg4 stream
        for (ii = 0; ii < len-1; ii++)
        {
            strid = (strid << 8) | buf[ii];
            if ( strid == 0x1b6 )
            {
                if ((buf[ii+1] & 0xC0) == 0)
                    return 1;
            }
        }
        // didn't find an I-frame
        return 0;
    }

    // we don't understand the stream type so just say "yes" otherwise
    // we'll discard all the video.
    return 1;
}