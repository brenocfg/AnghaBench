#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
typedef  int /*<<< orphan*/  hb_work_object_t ;
struct TYPE_7__ {int num; int den; } ;
struct TYPE_8__ {char* name; int bitrate; int flags; int sample_bit_depth; int samples_per_frame; int /*<<< orphan*/ * channel_map; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  matrix_encoding; TYPE_1__ rate; } ;
typedef  TYPE_2__ hb_work_info_t ;
struct TYPE_9__ {int* data; } ;
typedef  TYPE_3__ hb_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  AV_MATRIX_ENCODING_NONE ; 
 int /*<<< orphan*/  hb_libav_chan_map ; 
 int /*<<< orphan*/ * hdr2layout ; 
 int* hdr2samplerate ; 
 int* hdr2samplesize ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int declpcmBSInfo( hb_work_object_t *w, const hb_buffer_t *b,
                          hb_work_info_t *info )
{
    int nchannels  = ( b->data[4] & 7 ) + 1;
    int sample_size = hdr2samplesize[b->data[4] >> 6];

    int rate = hdr2samplerate[ ( b->data[4] >> 4 ) & 0x3 ];
    int bitrate = rate * sample_size * nchannels;
    int64_t duration = b->data[0] * 150;

    memset( info, 0, sizeof(*info) );

    info->name = "LPCM";
    info->rate.num = rate;
    info->rate.den = 1;
    info->bitrate = bitrate;
    info->flags = ( b->data[3] << 16 ) | ( b->data[4] << 8 ) | b->data[5];
    info->matrix_encoding = AV_MATRIX_ENCODING_NONE;
    info->channel_layout = hdr2layout[nchannels - 1];
    info->channel_map = &hb_libav_chan_map;
    info->sample_bit_depth = sample_size;
    info->samples_per_frame = ( duration * rate ) / 90000;

    return 1;
}