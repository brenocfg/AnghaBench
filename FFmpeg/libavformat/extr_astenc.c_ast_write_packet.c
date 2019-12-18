#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int fbs; } ;
struct TYPE_11__ {int channels; } ;
struct TYPE_10__ {TYPE_1__** streams; TYPE_5__* priv_data; int /*<<< orphan*/ * pb; } ;
struct TYPE_9__ {int size; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {scalar_t__ nb_frames; TYPE_4__* codecpar; } ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVCodecParameters ;
typedef  TYPE_5__ ASTMuxContext ;

/* Variables and functions */
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int ast_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    AVIOContext *pb = s->pb;
    ASTMuxContext *ast = s->priv_data;
    AVCodecParameters *par = s->streams[0]->codecpar;
    int size = pkt->size / par->channels;

    if (s->streams[0]->nb_frames == 0)
        ast->fbs = size;

    ffio_wfourcc(pb, "BLCK");
    avio_wb32(pb, size); /* Block size */

    /* padding */
    avio_wb64(pb, 0);
    avio_wb64(pb, 0);
    avio_wb64(pb, 0);

    avio_write(pb, pkt->data, pkt->size);

    return 0;
}