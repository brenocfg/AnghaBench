#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct playlist** buffer; } ;
struct playlist {TYPE_4__* ctx; scalar_t__ input_next_requested; int /*<<< orphan*/  input_next; scalar_t__ input_read_done; int /*<<< orphan*/  input; TYPE_1__ pb; int /*<<< orphan*/  pkt; struct playlist** init_sec_buf; int /*<<< orphan*/  id3_deferred_extra; int /*<<< orphan*/  id3_initial; struct playlist** id3_buf; struct playlist** renditions; struct playlist** main_streams; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pb; } ;
struct TYPE_6__ {int n_playlists; struct playlist** playlists; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_2__ HLSContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (struct playlist*) ; 
 int /*<<< orphan*/  av_freep (struct playlist***) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avformat_close_input (TYPE_4__**) ; 
 int /*<<< orphan*/  ff_format_io_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_id3v2_free_extra_meta (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_init_section_list (struct playlist*) ; 
 int /*<<< orphan*/  free_segment_list (struct playlist*) ; 

__attribute__((used)) static void free_playlist_list(HLSContext *c)
{
    int i;
    for (i = 0; i < c->n_playlists; i++) {
        struct playlist *pls = c->playlists[i];
        free_segment_list(pls);
        free_init_section_list(pls);
        av_freep(&pls->main_streams);
        av_freep(&pls->renditions);
        av_freep(&pls->id3_buf);
        av_dict_free(&pls->id3_initial);
        ff_id3v2_free_extra_meta(&pls->id3_deferred_extra);
        av_freep(&pls->init_sec_buf);
        av_packet_unref(&pls->pkt);
        av_freep(&pls->pb.buffer);
        ff_format_io_close(c->ctx, &pls->input);
        pls->input_read_done = 0;
        ff_format_io_close(c->ctx, &pls->input_next);
        pls->input_next_requested = 0;
        if (pls->ctx) {
            pls->ctx->pb = NULL;
            avformat_close_input(&pls->ctx);
        }
        av_free(pls);
    }
    av_freep(&c->playlists);
    c->n_playlists = 0;
}