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
struct TYPE_8__ {int extradata_size; int codec_id; scalar_t__ extradata; } ;
struct TYPE_7__ {int /*<<< orphan*/  pb; TYPE_1__** streams; } ;
struct TYPE_6__ {TYPE_3__* codecpar; } ;
typedef  TYPE_2__ AVFormatContext ;
typedef  TYPE_3__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
#define  AV_CODEC_ID_A64_MULTI 129 
#define  AV_CODEC_ID_A64_MULTI5 128 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RB32 (scalar_t__) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int a64_write_header(AVFormatContext *s)
{
    AVCodecParameters *par = s->streams[0]->codecpar;
    uint8_t header[5] = {
        0x00, //load
        0x40, //address
        0x00, //mode
        0x00, //charset_lifetime (multi only)
        0x00  //fps in 50/fps;
    };

    if (par->extradata_size < 4) {
        av_log(s, AV_LOG_ERROR, "Missing extradata\n");
        return AVERROR_INVALIDDATA;
    }

    switch (par->codec_id) {
    case AV_CODEC_ID_A64_MULTI:
        header[2] = 0x00;
        header[3] = AV_RB32(par->extradata+0);
        header[4] = 2;
        break;
    case AV_CODEC_ID_A64_MULTI5:
        header[2] = 0x01;
        header[3] = AV_RB32(par->extradata+0);
        header[4] = 3;
        break;
    default:
        return AVERROR_INVALIDDATA;
    }
    avio_write(s->pb, header, 2);
    return 0;
}