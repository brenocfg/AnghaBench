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
struct TYPE_7__ {TYPE_1__* dstpad; } ;
struct TYPE_6__ {int /*<<< orphan*/ * (* get_audio_buffer ) (TYPE_2__*,int) ;} ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_2__ AVFilterLink ;

/* Variables and functions */
 int /*<<< orphan*/ * ff_default_get_audio_buffer (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * stub1 (TYPE_2__*,int) ; 

AVFrame *ff_get_audio_buffer(AVFilterLink *link, int nb_samples)
{
    AVFrame *ret = NULL;

    if (link->dstpad->get_audio_buffer)
        ret = link->dstpad->get_audio_buffer(link, nb_samples);

    if (!ret)
        ret = ff_default_get_audio_buffer(link, nb_samples);

    return ret;
}