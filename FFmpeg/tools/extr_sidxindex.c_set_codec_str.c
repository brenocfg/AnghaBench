#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int codec_id; int extradata_size; int* extradata; } ;
typedef  TYPE_1__ AVCodecParameters ;

/* Variables and functions */
#define  AV_CODEC_ID_AAC 129 
#define  AV_CODEC_ID_H264 128 
 int AV_RB16 (int*) ; 
 int /*<<< orphan*/  av_strlcatf (char*,int,char*,int,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*) ; 

__attribute__((used)) static void set_codec_str(AVCodecParameters *codecpar, char *str, int size)
{
    switch (codecpar->codec_id) {
    case AV_CODEC_ID_H264:
        snprintf(str, size, "avc1");
        if (codecpar->extradata_size >= 4 && codecpar->extradata[0] == 1) {
            av_strlcatf(str, size, ".%02x%02x%02x",
                        codecpar->extradata[1], codecpar->extradata[2],
                        codecpar->extradata[3]);
        }
        break;
    case AV_CODEC_ID_AAC:
        snprintf(str, size, "mp4a.40"); // 0x40 is the mp4 object type for AAC
        if (codecpar->extradata_size >= 2) {
            int aot = codecpar->extradata[0] >> 3;
            if (aot == 31)
                aot = ((AV_RB16(codecpar->extradata) >> 5) & 0x3f) + 32;
            av_strlcatf(str, size, ".%d", aot);
        }
        break;
    }
}