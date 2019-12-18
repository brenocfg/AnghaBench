#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct representation {int /*<<< orphan*/  stream_index; int /*<<< orphan*/  input; int /*<<< orphan*/  parent; scalar_t__ ctx; int /*<<< orphan*/  cur_seq_no; scalar_t__ init_sec_buf_read_offset; scalar_t__ cur_seg_offset; TYPE_1__* assoc_stream; } ;
struct TYPE_2__ {scalar_t__ discard; } ;
typedef  int /*<<< orphan*/  AVFormatContext ;

/* Variables and functions */
 scalar_t__ AVDISCARD_ALL ; 
 int /*<<< orphan*/  AV_LOG_INFO ; 
 int /*<<< orphan*/  FFMAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_demux_for_component (struct representation*) ; 
 int /*<<< orphan*/  ff_format_io_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reopen_demux_for_component (int /*<<< orphan*/ *,struct representation*) ; 

__attribute__((used)) static void recheck_discard_flags(AVFormatContext *s, struct representation **p, int n)
{
    int i, j;

    for (i = 0; i < n; i++) {
        struct representation *pls = p[i];
        int needed = !pls->assoc_stream || pls->assoc_stream->discard < AVDISCARD_ALL;

        if (needed && !pls->ctx) {
            pls->cur_seg_offset = 0;
            pls->init_sec_buf_read_offset = 0;
            /* Catch up */
            for (j = 0; j < n; j++) {
                pls->cur_seq_no = FFMAX(pls->cur_seq_no, p[j]->cur_seq_no);
            }
            reopen_demux_for_component(s, pls);
            av_log(s, AV_LOG_INFO, "Now receiving stream_index %d\n", pls->stream_index);
        } else if (!needed && pls->ctx) {
            close_demux_for_component(pls);
            ff_format_io_close(pls->parent, &pls->input);
            av_log(s, AV_LOG_INFO, "No longer receiving stream_index %d\n", pls->stream_index);
        }
    }
}