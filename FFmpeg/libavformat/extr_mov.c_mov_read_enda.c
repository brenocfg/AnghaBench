#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nb_streams; TYPE_3__** streams; } ;
struct TYPE_8__ {TYPE_1__* codecpar; } ;
struct TYPE_7__ {TYPE_5__* fc; } ;
struct TYPE_6__ {int codec_id; } ;
typedef  TYPE_2__ MOVContext ;
typedef  int /*<<< orphan*/  MOVAtom ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;

/* Variables and functions */
#define  AV_CODEC_ID_PCM_F32BE 131 
 int AV_CODEC_ID_PCM_F32LE ; 
#define  AV_CODEC_ID_PCM_F64BE 130 
 int AV_CODEC_ID_PCM_F64LE ; 
#define  AV_CODEC_ID_PCM_S24BE 129 
 int AV_CODEC_ID_PCM_S24LE ; 
#define  AV_CODEC_ID_PCM_S32BE 128 
 int AV_CODEC_ID_PCM_S32LE ; 
 int /*<<< orphan*/  AV_LOG_TRACE ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int) ; 
 int avio_rb16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mov_read_enda(MOVContext *c, AVIOContext *pb, MOVAtom atom)
{
    AVStream *st;
    int little_endian;

    if (c->fc->nb_streams < 1)
        return 0;
    st = c->fc->streams[c->fc->nb_streams-1];

    little_endian = avio_rb16(pb) & 0xFF;
    av_log(c->fc, AV_LOG_TRACE, "enda %d\n", little_endian);
    if (little_endian == 1) {
        switch (st->codecpar->codec_id) {
        case AV_CODEC_ID_PCM_S24BE:
            st->codecpar->codec_id = AV_CODEC_ID_PCM_S24LE;
            break;
        case AV_CODEC_ID_PCM_S32BE:
            st->codecpar->codec_id = AV_CODEC_ID_PCM_S32LE;
            break;
        case AV_CODEC_ID_PCM_F32BE:
            st->codecpar->codec_id = AV_CODEC_ID_PCM_F32LE;
            break;
        case AV_CODEC_ID_PCM_F64BE:
            st->codecpar->codec_id = AV_CODEC_ID_PCM_F64LE;
            break;
        default:
            break;
        }
    }
    return 0;
}