#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* priv_data; } ;
struct TYPE_6__ {int /*<<< orphan*/  base_url; int /*<<< orphan*/  avio_opts; } ;
typedef  TYPE_1__ DASHContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_audio_list (TYPE_1__*) ; 
 int /*<<< orphan*/  free_video_list (TYPE_1__*) ; 

__attribute__((used)) static int dash_close(AVFormatContext *s)
{
    DASHContext *c = s->priv_data;
    free_audio_list(c);
    free_video_list(c);
    av_dict_free(&c->avio_opts);
    av_freep(&c->base_url);
    return 0;
}