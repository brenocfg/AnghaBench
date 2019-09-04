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
struct TYPE_4__ {int nb_bsfs; int /*<<< orphan*/ * bsfs; } ;
typedef  TYPE_1__ AVBSFList ;

/* Variables and functions */
 int /*<<< orphan*/  av_bsf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 

void av_bsf_list_free(AVBSFList **lst)
{
    int i;

    if (!*lst)
        return;

    for (i = 0; i < (*lst)->nb_bsfs; ++i)
        av_bsf_free(&(*lst)->bsfs[i]);
    av_free((*lst)->bsfs);
    av_freep(lst);
}