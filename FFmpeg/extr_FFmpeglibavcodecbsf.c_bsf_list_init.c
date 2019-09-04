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
struct TYPE_7__ {void* time_base_out; int /*<<< orphan*/ * par_out; void* time_base_in; int /*<<< orphan*/  par_in; } ;
struct TYPE_6__ {int /*<<< orphan*/  par_out; void* time_base_out; void* time_base_in; int /*<<< orphan*/ * par_in; TYPE_1__* priv_data; } ;
struct TYPE_5__ {int nb_bsfs; TYPE_4__** bsfs; } ;
typedef  TYPE_1__ BSFListContext ;
typedef  void* AVRational ;
typedef  int /*<<< orphan*/  AVCodecParameters ;
typedef  TYPE_2__ AVBSFContext ;

/* Variables and functions */
 int av_bsf_init (TYPE_4__*) ; 
 int avcodec_parameters_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int bsf_list_init(AVBSFContext *bsf)
{
    BSFListContext *lst = bsf->priv_data;
    int ret, i;
    const AVCodecParameters *cod_par = bsf->par_in;
    AVRational tb = bsf->time_base_in;

    for (i = 0; i < lst->nb_bsfs; ++i) {
        ret = avcodec_parameters_copy(lst->bsfs[i]->par_in, cod_par);
        if (ret < 0)
            goto fail;

        lst->bsfs[i]->time_base_in = tb;

        ret = av_bsf_init(lst->bsfs[i]);
        if (ret < 0)
            goto fail;

        cod_par = lst->bsfs[i]->par_out;
        tb = lst->bsfs[i]->time_base_out;
    }

    bsf->time_base_out = tb;
    ret = avcodec_parameters_copy(bsf->par_out, cod_par);

fail:
    return ret;
}