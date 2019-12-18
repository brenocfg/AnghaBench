#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct representation* buffer; } ;
struct representation {struct representation* url_template; TYPE_2__* ctx; int /*<<< orphan*/  input; int /*<<< orphan*/  parent; TYPE_1__ pb; struct representation* init_sec_buf; int /*<<< orphan*/  init_section; int /*<<< orphan*/  cur_seg; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pb; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (struct representation**) ; 
 int /*<<< orphan*/  avformat_close_input (TYPE_2__**) ; 
 int /*<<< orphan*/  ff_format_io_close (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_fragment (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_fragment_list (struct representation*) ; 
 int /*<<< orphan*/  free_timelines_list (struct representation*) ; 

__attribute__((used)) static void free_representation(struct representation *pls)
{
    free_fragment_list(pls);
    free_timelines_list(pls);
    free_fragment(&pls->cur_seg);
    free_fragment(&pls->init_section);
    av_freep(&pls->init_sec_buf);
    av_freep(&pls->pb.buffer);
    ff_format_io_close(pls->parent, &pls->input);
    if (pls->ctx) {
        pls->ctx->pb = NULL;
        avformat_close_input(&pls->ctx);
    }

    av_freep(&pls->url_template);
    av_freep(&pls);
}