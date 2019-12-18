#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int residue_count; int codebook_count; int floor_count; int mapping_count; TYPE_6__* mappings; TYPE_6__* floors; TYPE_6__* codebooks; int /*<<< orphan*/ * mdct; TYPE_6__* modes; TYPE_6__* residues; TYPE_6__* fdsp; TYPE_6__* saved; TYPE_6__* channel_residues; } ;
typedef  TYPE_4__ vorbis_context ;
struct TYPE_8__ {TYPE_6__* list; } ;
struct TYPE_7__ {TYPE_6__* lsp; TYPE_6__* book_list; TYPE_6__** map; } ;
struct TYPE_9__ {TYPE_2__ t1; TYPE_1__ t0; } ;
struct TYPE_11__ {scalar_t__ floor_type; struct TYPE_11__* mux; struct TYPE_11__* angle; struct TYPE_11__* magnitude; TYPE_3__ data; int /*<<< orphan*/  vlc; struct TYPE_11__* codevectors; struct TYPE_11__* classifs; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_6__**) ; 
 int /*<<< orphan*/  ff_free_vlc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_mdct_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vorbis_free(vorbis_context *vc)
{
    int i;

    av_freep(&vc->channel_residues);
    av_freep(&vc->saved);
    av_freep(&vc->fdsp);

    if (vc->residues)
        for (i = 0; i < vc->residue_count; i++)
            av_freep(&vc->residues[i].classifs);
    av_freep(&vc->residues);
    av_freep(&vc->modes);

    ff_mdct_end(&vc->mdct[0]);
    ff_mdct_end(&vc->mdct[1]);

    if (vc->codebooks)
        for (i = 0; i < vc->codebook_count; ++i) {
            av_freep(&vc->codebooks[i].codevectors);
            ff_free_vlc(&vc->codebooks[i].vlc);
        }
    av_freep(&vc->codebooks);

    if (vc->floors)
        for (i = 0; i < vc->floor_count; ++i) {
            if (vc->floors[i].floor_type == 0) {
                av_freep(&vc->floors[i].data.t0.map[0]);
                av_freep(&vc->floors[i].data.t0.map[1]);
                av_freep(&vc->floors[i].data.t0.book_list);
                av_freep(&vc->floors[i].data.t0.lsp);
            } else {
                av_freep(&vc->floors[i].data.t1.list);
            }
        }
    av_freep(&vc->floors);

    if (vc->mappings)
        for (i = 0; i < vc->mapping_count; ++i) {
            av_freep(&vc->mappings[i].magnitude);
            av_freep(&vc->mappings[i].angle);
            av_freep(&vc->mappings[i].mux);
        }
    av_freep(&vc->mappings);
}