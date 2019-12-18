#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  AVDictionary ;
typedef  int /*<<< orphan*/  AVBitStreamFilter ;
typedef  int /*<<< orphan*/  AVBSFList ;
typedef  int /*<<< orphan*/  AVBSFContext ;

/* Variables and functions */
 int AVERROR_BSF_NOT_FOUND ; 
 int /*<<< orphan*/  AV_OPT_SEARCH_CHILDREN ; 
 int av_bsf_alloc (int /*<<< orphan*/  const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_bsf_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * av_bsf_get_by_name (char const*) ; 
 int av_bsf_list_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int av_opt_set_dict2 (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

int av_bsf_list_append2(AVBSFList *lst, const char *bsf_name, AVDictionary ** options)
{
    int ret;
    const AVBitStreamFilter *filter;
    AVBSFContext *bsf;

    filter = av_bsf_get_by_name(bsf_name);
    if (!filter)
        return AVERROR_BSF_NOT_FOUND;

    ret = av_bsf_alloc(filter, &bsf);
    if (ret < 0)
        return ret;

    if (options) {
        ret = av_opt_set_dict2(bsf, options, AV_OPT_SEARCH_CHILDREN);
        if (ret < 0)
            goto end;
    }

    ret = av_bsf_list_append(lst, bsf);

end:
    if (ret < 0)
        av_bsf_free(&bsf);

    return ret;
}