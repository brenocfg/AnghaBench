#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct eac3_info {scalar_t__ tag; int /*<<< orphan*/  cenc; struct eac3_info* vos_data; scalar_t__ vos_len; struct eac3_info* eac3_priv; int /*<<< orphan*/  pkt; int /*<<< orphan*/  cover_image; struct eac3_info* frag_info; struct eac3_info* cluster; struct eac3_info* par; struct eac3_info* extradata; } ;
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int chapter_track; int nb_streams; struct eac3_info* tracks; scalar_t__ nb_meta_tmcd; } ;
typedef  TYPE_1__ MOVMuxContext ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 scalar_t__ MKTAG (char,char,char,char) ; 
 int /*<<< orphan*/  av_freep (struct eac3_info**) ; 
 int /*<<< orphan*/  av_packet_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_mov_cenc_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_mov_close_hinting (struct eac3_info*) ; 

__attribute__((used)) static void mov_free(AVFormatContext *s)
{
    MOVMuxContext *mov = s->priv_data;
    int i;

    if (mov->chapter_track) {
        if (mov->tracks[mov->chapter_track].par)
            av_freep(&mov->tracks[mov->chapter_track].par->extradata);
        av_freep(&mov->tracks[mov->chapter_track].par);
    }

    for (i = 0; i < mov->nb_streams; i++) {
        if (mov->tracks[i].tag == MKTAG('r','t','p',' '))
            ff_mov_close_hinting(&mov->tracks[i]);
        else if (mov->tracks[i].tag == MKTAG('t','m','c','d') && mov->nb_meta_tmcd)
            av_freep(&mov->tracks[i].par);
        av_freep(&mov->tracks[i].cluster);
        av_freep(&mov->tracks[i].frag_info);
        av_packet_unref(&mov->tracks[i].cover_image);

        if (mov->tracks[i].eac3_priv) {
            struct eac3_info *info = mov->tracks[i].eac3_priv;
            av_packet_unref(&info->pkt);
            av_freep(&mov->tracks[i].eac3_priv);
        }
        if (mov->tracks[i].vos_len)
            av_freep(&mov->tracks[i].vos_data);

        ff_mov_cenc_free(&mov->tracks[i].cenc);
    }

    av_freep(&mov->tracks);
}