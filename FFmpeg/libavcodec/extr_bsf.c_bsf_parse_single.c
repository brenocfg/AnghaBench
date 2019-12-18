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
typedef  int /*<<< orphan*/  AVBSFList ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int av_bsf_list_append2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_dict_free (int /*<<< orphan*/ **) ; 
 int av_dict_parse_string (int /*<<< orphan*/ **,char*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 char* av_strdup (char const*) ; 
 char* av_strtok (char*,char*,char**) ; 

__attribute__((used)) static int bsf_parse_single(const char *str, AVBSFList *bsf_lst)
{
    char *bsf_name, *bsf_options_str, *buf;
    AVDictionary *bsf_options = NULL;
    int ret = 0;

    if (!(buf = av_strdup(str)))
        return AVERROR(ENOMEM);

    bsf_name = av_strtok(buf, "=", &bsf_options_str);
    if (!bsf_name) {
        ret = AVERROR(EINVAL);
        goto end;
    }

    if (bsf_options_str) {
        ret = av_dict_parse_string(&bsf_options, bsf_options_str, "=", ":", 0);
        if (ret < 0)
            goto end;
    }

    ret = av_bsf_list_append2(bsf_lst, bsf_name, &bsf_options);

    av_dict_free(&bsf_options);
end:
    av_free(buf);
    return ret;
}