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
struct TYPE_5__ {TYPE_1__* priv_data; } ;
struct TYPE_4__ {int nb_bsfs; scalar_t__ flushed_idx; scalar_t__ idx; int /*<<< orphan*/ * bsfs; } ;
typedef  TYPE_1__ BSFListContext ;
typedef  TYPE_2__ AVBSFContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_bsf_flush (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bsf_list_flush(AVBSFContext *bsf)
{
    BSFListContext *lst = bsf->priv_data;

    for (int i = 0; i < lst->nb_bsfs; i++)
        av_bsf_flush(lst->bsfs[i]);
    lst->idx = lst->flushed_idx = 0;
}