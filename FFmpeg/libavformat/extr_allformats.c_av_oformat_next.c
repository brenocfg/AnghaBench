#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; } ;
typedef  TYPE_1__ AVOutputFormat ;

/* Variables and functions */
 int /*<<< orphan*/  av_format_init_next ; 
 int /*<<< orphan*/  av_format_next_init ; 
 scalar_t__ av_muxer_iterate (void**) ; 
 int /*<<< orphan*/  ff_thread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

AVOutputFormat *av_oformat_next(const AVOutputFormat *f)
{
    ff_thread_once(&av_format_next_init, av_format_init_next);

    if (f)
#if FF_API_AVIOFORMAT
        return f->next;
#else
        return (AVOutputFormat *) f->next;
#endif
    else {
        void *opaque = NULL;
        return (AVOutputFormat *)av_muxer_iterate(&opaque);
    }
}