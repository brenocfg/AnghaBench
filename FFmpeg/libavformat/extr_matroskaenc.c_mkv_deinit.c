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
struct TYPE_7__ {struct TYPE_7__* entries; } ;
struct TYPE_6__ {TYPE_1__* priv_data; } ;
struct TYPE_5__ {TYPE_4__* tracks; TYPE_4__* attachments; TYPE_4__* cues; TYPE_4__* seekhead; int /*<<< orphan*/  tags_bc; int /*<<< orphan*/  tracks_bc; int /*<<< orphan*/  info_bc; int /*<<< orphan*/  cluster_bc; } ;
typedef  TYPE_1__ MatroskaMuxContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_4__**) ; 
 int /*<<< orphan*/  ffio_free_dyn_buf (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mkv_deinit(AVFormatContext *s)
{
    MatroskaMuxContext *mkv = s->priv_data;

    ffio_free_dyn_buf(&mkv->cluster_bc);
    ffio_free_dyn_buf(&mkv->info_bc);
    ffio_free_dyn_buf(&mkv->tracks_bc);
    ffio_free_dyn_buf(&mkv->tags_bc);

    if (mkv->seekhead) {
        av_freep(&mkv->seekhead->entries);
        av_freep(&mkv->seekhead);
    }
    if (mkv->cues) {
        av_freep(&mkv->cues->entries);
        av_freep(&mkv->cues);
    }
    if (mkv->attachments) {
        av_freep(&mkv->attachments->entries);
        av_freep(&mkv->attachments);
    }
    av_freep(&mkv->tracks);
}