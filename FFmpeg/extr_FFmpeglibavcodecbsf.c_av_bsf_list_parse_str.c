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
typedef  int /*<<< orphan*/  AVBSFList ;
typedef  int /*<<< orphan*/  AVBSFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int av_bsf_get_null_filter (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * av_bsf_list_alloc () ; 
 int av_bsf_list_finalize (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_bsf_list_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_strdup (char const*) ; 
 char* av_strtok (char*,char*,char**) ; 
 int bsf_parse_single (char*,int /*<<< orphan*/ *) ; 

int av_bsf_list_parse_str(const char *str, AVBSFContext **bsf_lst)
{
    AVBSFList *lst;
    char *bsf_str, *buf, *dup, *saveptr;
    int ret;

    if (!str)
        return av_bsf_get_null_filter(bsf_lst);

    lst = av_bsf_list_alloc();
    if (!lst)
        return AVERROR(ENOMEM);

    if (!(dup = buf = av_strdup(str))) {
        ret = AVERROR(ENOMEM);
        goto end;
    }

    while (1) {
        bsf_str = av_strtok(buf, ",", &saveptr);
        if (!bsf_str)
            break;

        ret = bsf_parse_single(bsf_str, lst);
        if (ret < 0)
            goto end;

        buf = NULL;
    }

    ret = av_bsf_list_finalize(&lst, bsf_lst);
end:
    if (ret < 0)
        av_bsf_list_free(&lst);
    av_free(dup);
    return ret;
}