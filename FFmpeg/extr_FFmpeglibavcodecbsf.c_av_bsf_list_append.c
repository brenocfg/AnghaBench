#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  nb_bsfs; int /*<<< orphan*/  bsfs; } ;
typedef  TYPE_1__ AVBSFList ;
typedef  int /*<<< orphan*/  AVBSFContext ;

/* Variables and functions */
 int av_dynarray_add_nofree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int av_bsf_list_append(AVBSFList *lst, AVBSFContext *bsf)
{
    return av_dynarray_add_nofree(&lst->bsfs, &lst->nb_bsfs, bsf);
}