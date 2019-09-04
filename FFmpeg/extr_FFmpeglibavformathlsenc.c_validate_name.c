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

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* av_basename (char const*) ; 
 char* av_dirname (char*) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 char* av_strdup (char const*) ; 
 scalar_t__ av_stristr (char const*,char*) ; 

__attribute__((used)) static int validate_name(int nb_vs, const char *fn)
{
    const char *filename, *subdir_name;
    char *fn_dup = NULL;
    int ret = 0;

    if (!fn) {
        ret = AVERROR(EINVAL);
        goto fail;
    }

    fn_dup = av_strdup(fn);
    if (!fn_dup) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    filename = av_basename(fn);
    subdir_name = av_dirname(fn_dup);

    if (nb_vs > 1 && !av_stristr(filename, "%v") && !av_stristr(subdir_name, "%v")) {
        av_log(NULL, AV_LOG_ERROR, "More than 1 variant streams are present, %%v is expected in the filename %s\n",
                fn);
        ret = AVERROR(EINVAL);
        goto fail;
    }

    if (av_stristr(filename, "%v") && av_stristr(subdir_name, "%v")) {
        av_log(NULL, AV_LOG_ERROR, "%%v is expected either in filename or in the sub-directory name of file %s\n",
                fn);
        ret = AVERROR(EINVAL);
        goto fail;
    }

fail:
    av_freep(&fn_dup);
    return ret;
}