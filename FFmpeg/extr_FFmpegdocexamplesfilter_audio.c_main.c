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
typedef  char uint8_t ;
struct AVMD5 {int dummy; } ;
typedef  int /*<<< orphan*/  errstr ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  int /*<<< orphan*/  AVFilterGraph ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int /*<<< orphan*/  EAGAIN ; 
 float FRAME_SIZE ; 
 float INPUT_SAMPLERATE ; 
 float atof (char*) ; 
 int av_buffersink_get_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int av_buffersrc_add_frame (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (struct AVMD5**) ; 
 struct AVMD5* av_md5_alloc () ; 
 int /*<<< orphan*/  av_strerror (int,char*,int) ; 
 int /*<<< orphan*/  avfilter_graph_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int get_input (int /*<<< orphan*/ *,int) ; 
 int init_filter_graph (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int process_output (struct AVMD5*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char *argv[])
{
    struct AVMD5 *md5;
    AVFilterGraph *graph;
    AVFilterContext *src, *sink;
    AVFrame *frame;
    uint8_t errstr[1024];
    float duration;
    int err, nb_frames, i;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <duration>\n", argv[0]);
        return 1;
    }

    duration  = atof(argv[1]);
    nb_frames = duration * INPUT_SAMPLERATE / FRAME_SIZE;
    if (nb_frames <= 0) {
        fprintf(stderr, "Invalid duration: %s\n", argv[1]);
        return 1;
    }

    /* Allocate the frame we will be using to store the data. */
    frame  = av_frame_alloc();
    if (!frame) {
        fprintf(stderr, "Error allocating the frame\n");
        return 1;
    }

    md5 = av_md5_alloc();
    if (!md5) {
        fprintf(stderr, "Error allocating the MD5 context\n");
        return 1;
    }

    /* Set up the filtergraph. */
    err = init_filter_graph(&graph, &src, &sink);
    if (err < 0) {
        fprintf(stderr, "Unable to init filter graph:");
        goto fail;
    }

    /* the main filtering loop */
    for (i = 0; i < nb_frames; i++) {
        /* get an input frame to be filtered */
        err = get_input(frame, i);
        if (err < 0) {
            fprintf(stderr, "Error generating input frame:");
            goto fail;
        }

        /* Send the frame to the input of the filtergraph. */
        err = av_buffersrc_add_frame(src, frame);
        if (err < 0) {
            av_frame_unref(frame);
            fprintf(stderr, "Error submitting the frame to the filtergraph:");
            goto fail;
        }

        /* Get all the filtered output that is available. */
        while ((err = av_buffersink_get_frame(sink, frame)) >= 0) {
            /* now do something with our filtered frame */
            err = process_output(md5, frame);
            if (err < 0) {
                fprintf(stderr, "Error processing the filtered frame:");
                goto fail;
            }
            av_frame_unref(frame);
        }

        if (err == AVERROR(EAGAIN)) {
            /* Need to feed more frames in. */
            continue;
        } else if (err == AVERROR_EOF) {
            /* Nothing more to do, finish. */
            break;
        } else if (err < 0) {
            /* An error occurred. */
            fprintf(stderr, "Error filtering the data:");
            goto fail;
        }
    }

    avfilter_graph_free(&graph);
    av_frame_free(&frame);
    av_freep(&md5);

    return 0;

fail:
    av_strerror(err, errstr, sizeof(errstr));
    fprintf(stderr, "%s\n", errstr);
    return 1;
}