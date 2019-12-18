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
typedef  TYPE_1__ AVCodec ;

/* Variables and functions */
 int /*<<< orphan*/  av_codec_init_next ; 
 int /*<<< orphan*/  av_codec_next_init ; 
 scalar_t__* codec_list ; 
 int /*<<< orphan*/  ff_thread_once (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

AVCodec *av_codec_next(const AVCodec *c)
{
    ff_thread_once(&av_codec_next_init, av_codec_init_next);

    if (c)
        return c->next;
    else
        return (AVCodec*)codec_list[0];
}