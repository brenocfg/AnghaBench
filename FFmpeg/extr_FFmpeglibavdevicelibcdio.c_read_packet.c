#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_12__ {TYPE_1__** streams; TYPE_2__* priv_data; } ;
struct TYPE_11__ {int /*<<< orphan*/  data; } ;
struct TYPE_10__ {scalar_t__ last_sector; int /*<<< orphan*/  drive; int /*<<< orphan*/  paranoia; } ;
struct TYPE_9__ {scalar_t__ cur_dts; } ;
typedef  TYPE_2__ CDIOContext ;
typedef  TYPE_3__ AVPacket ;
typedef  TYPE_4__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_EOF ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  CDIO_CD_FRAMESIZE_RAW ; 
 int /*<<< orphan*/  av_log (TYPE_4__*,int /*<<< orphan*/ ,char*,char*) ; 
 int av_new_packet (TYPE_3__*,int /*<<< orphan*/ ) ; 
 char* cdio_cddap_errors (int /*<<< orphan*/ ) ; 
 char* cdio_cddap_messages (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cdio_paranoia_read (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int read_packet(AVFormatContext *ctx, AVPacket *pkt)
{
    CDIOContext *s = ctx->priv_data;
    int ret;
    uint16_t *buf;
    char *err = NULL;

    if (ctx->streams[0]->cur_dts > s->last_sector)
        return AVERROR_EOF;

    buf = cdio_paranoia_read(s->paranoia, NULL);
    if (!buf)
        return AVERROR_EOF;

    if (err = cdio_cddap_errors(s->drive)) {
        av_log(ctx, AV_LOG_ERROR, "%s\n", err);
        free(err);
        err = NULL;
    }
    if (err = cdio_cddap_messages(s->drive)) {
        av_log(ctx, AV_LOG_VERBOSE, "%s\n", err);
        free(err);
        err = NULL;
    }

    if ((ret = av_new_packet(pkt, CDIO_CD_FRAMESIZE_RAW)) < 0)
        return ret;
    memcpy(pkt->data, buf, CDIO_CD_FRAMESIZE_RAW);
    return 0;
}