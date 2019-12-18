#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int previous_blocksize; int mode_count; int const mode_mask; int* mode_blocksize; int const prev_mask; int* blocksize; scalar_t__ valid_extradata; } ;
typedef  TYPE_1__ AVVorbisParseContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int VORBIS_FLAG_COMMENT ; 
 int VORBIS_FLAG_HEADER ; 
 int VORBIS_FLAG_SETUP ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 

int av_vorbis_parse_frame_flags(AVVorbisParseContext *s, const uint8_t *buf,
                                int buf_size, int *flags)
{
    int duration = 0;

    if (s->valid_extradata && buf_size > 0) {
        int mode, current_blocksize;
        int previous_blocksize = s->previous_blocksize;

        if (buf[0] & 1) {
            /* If the user doesn't care about special packets, it's a bad one. */
            if (!flags)
                goto bad_packet;

            /* Set the flag for which kind of special packet it is. */
            if (buf[0] == 1)
                *flags |= VORBIS_FLAG_HEADER;
            else if (buf[0] == 3)
                *flags |= VORBIS_FLAG_COMMENT;
            else if (buf[0] == 5)
                *flags |= VORBIS_FLAG_SETUP;
            else
                goto bad_packet;

            /* Special packets have no duration. */
            return 0;

bad_packet:
            av_log(s, AV_LOG_ERROR, "Invalid packet\n");
            return AVERROR_INVALIDDATA;
        }
        if (s->mode_count == 1)
            mode = 0;
        else
            mode = (buf[0] & s->mode_mask) >> 1;
        if (mode >= s->mode_count) {
            av_log(s, AV_LOG_ERROR, "Invalid mode in packet\n");
            return AVERROR_INVALIDDATA;
        }
        if(s->mode_blocksize[mode]){
            int flag = !!(buf[0] & s->prev_mask);
            previous_blocksize = s->blocksize[flag];
        }
        current_blocksize     = s->blocksize[s->mode_blocksize[mode]];
        duration              = (previous_blocksize + current_blocksize) >> 2;
        s->previous_blocksize = current_blocksize;
    }

    return duration;
}