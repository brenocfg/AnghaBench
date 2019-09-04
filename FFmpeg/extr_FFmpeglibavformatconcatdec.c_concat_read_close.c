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
struct TYPE_7__ {unsigned int nb_streams; int /*<<< orphan*/  metadata; struct TYPE_7__* streams; scalar_t__ bsf; struct TYPE_7__* url; } ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {unsigned int nb_files; TYPE_4__* files; scalar_t__ avf; } ;
typedef  TYPE_1__ ConcatContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_bsf_free (scalar_t__*) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_4__**) ; 
 int /*<<< orphan*/  avformat_close_input (scalar_t__*) ; 

__attribute__((used)) static int concat_read_close(AVFormatContext *avf)
{
    ConcatContext *cat = avf->priv_data;
    unsigned i, j;

    for (i = 0; i < cat->nb_files; i++) {
        av_freep(&cat->files[i].url);
        for (j = 0; j < cat->files[i].nb_streams; j++) {
            if (cat->files[i].streams[j].bsf)
                av_bsf_free(&cat->files[i].streams[j].bsf);
        }
        av_freep(&cat->files[i].streams);
        av_dict_free(&cat->files[i].metadata);
    }
    if (cat->avf)
        avformat_close_input(&cat->avf);
    av_freep(&cat->files);
    return 0;
}