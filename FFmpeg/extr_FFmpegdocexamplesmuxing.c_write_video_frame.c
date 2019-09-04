#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  time_base; } ;
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {int /*<<< orphan*/  st; TYPE_3__* enc; } ;
typedef  TYPE_1__ OutputStream ;
typedef  TYPE_2__ AVPacket ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 char* av_err2str (int) ; 
 int /*<<< orphan*/  av_init_packet (TYPE_2__*) ; 
 int avcodec_encode_video2 (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * get_video_frame (TYPE_1__*) ; 
 int /*<<< orphan*/  stderr ; 
 int write_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int write_video_frame(AVFormatContext *oc, OutputStream *ost)
{
    int ret;
    AVCodecContext *c;
    AVFrame *frame;
    int got_packet = 0;
    AVPacket pkt = { 0 };

    c = ost->enc;

    frame = get_video_frame(ost);

    av_init_packet(&pkt);

    /* encode the image */
    ret = avcodec_encode_video2(c, &pkt, frame, &got_packet);
    if (ret < 0) {
        fprintf(stderr, "Error encoding video frame: %s\n", av_err2str(ret));
        exit(1);
    }

    if (got_packet) {
        ret = write_frame(oc, &c->time_base, ost->st, &pkt);
    } else {
        ret = 0;
    }

    if (ret < 0) {
        fprintf(stderr, "Error while writing video frame: %s\n", av_err2str(ret));
        exit(1);
    }

    return (frame || got_packet) ? 0 : 1;
}