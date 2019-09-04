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
typedef  int /*<<< orphan*/  AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int EXIT_FAILURE ; 
 char* av_err2str (int) ; 
 int avformat_alloc_output_context2 (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * avformat_new_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int initialize_fifo_tst_muxer_chain(AVFormatContext **oc)
{
    int ret = 0;
    AVStream *s;

    ret = avformat_alloc_output_context2(oc, NULL, "fifo", "-");
    if (ret) {
        fprintf(stderr, "Failed to create format context: %s\n",
                av_err2str(ret));
        return EXIT_FAILURE;
    }

    s = avformat_new_stream(*oc, NULL);
    if (!s) {
        fprintf(stderr, "Failed to create stream: %s\n",
                av_err2str(ret));
        ret = AVERROR(ENOMEM);
    }

    return ret;
}