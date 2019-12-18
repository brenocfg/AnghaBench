#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int video_frame_size; int audio_frequency; int audio_bits; scalar_t__ audio_stereo; void* audio_frame_size; void* video_frame_height; void* video_frame_width; } ;
struct TYPE_5__ {TYPE_1__ file_header; } ;
typedef  TYPE_1__ CinFileHeader ;
typedef  TYPE_2__ CinDemuxContext ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 void* avio_r8 (int /*<<< orphan*/ *) ; 
 void* avio_rl16 (int /*<<< orphan*/ *) ; 
 int avio_rl32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cin_read_file_header(CinDemuxContext *cin, AVIOContext *pb) {
    CinFileHeader *hdr = &cin->file_header;

    if (avio_rl32(pb) != 0x55AA0000)
        return AVERROR_INVALIDDATA;

    hdr->video_frame_size   = avio_rl32(pb);
    hdr->video_frame_width  = avio_rl16(pb);
    hdr->video_frame_height = avio_rl16(pb);
    hdr->audio_frequency    = avio_rl32(pb);
    hdr->audio_bits         = avio_r8(pb);
    hdr->audio_stereo       = avio_r8(pb);
    hdr->audio_frame_size   = avio_rl16(pb);

    if (hdr->audio_frequency != 22050 || hdr->audio_bits != 16 || hdr->audio_stereo != 0)
        return AVERROR_INVALIDDATA;

    return 0;
}