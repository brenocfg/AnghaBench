#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
#define  AV_CODEC_ID_OPUS 131 
#define  AV_CODEC_ID_VORBIS 130 
#define  AV_CODEC_ID_VP8 129 
#define  AV_CODEC_ID_VP9 128 

__attribute__((used)) static const char *get_codec_name(int codec_id)
{
    switch (codec_id) {
        case AV_CODEC_ID_VP8:
            return "vp8";
        case AV_CODEC_ID_VP9:
            return "vp9";
        case AV_CODEC_ID_VORBIS:
            return "vorbis";
        case AV_CODEC_ID_OPUS:
            return "opus";
    }
    return NULL;
}