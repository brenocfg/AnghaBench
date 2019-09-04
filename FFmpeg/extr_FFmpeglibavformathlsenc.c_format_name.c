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
 int AVERROR (scalar_t__) ; 
 scalar_t__ EEXIST ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENOMEM ; 
 char* av_dirname (char*) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 char* av_strdup (char*) ; 
 scalar_t__ av_stristr (char const*,char*) ; 
 int /*<<< orphan*/  av_strlcpy (char*,char*,int) ; 
 char* avio_find_protocol_name (char*) ; 
 scalar_t__ errno ; 
 int ff_mkdir_p (char const*) ; 
 int replace_int_data_in_filename (char**,char*,char,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int format_name(char *buf, int buf_len, int index)
{
    const char *proto, *dir;
    char *orig_buf_dup = NULL, *mod_buf = NULL, *mod_buf_dup = NULL;
    int ret = 0;

    if (!av_stristr(buf, "%v"))
        return ret;

    orig_buf_dup = av_strdup(buf);
    if (!orig_buf_dup) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    if (replace_int_data_in_filename(&mod_buf, orig_buf_dup, 'v', index) < 1) {
        ret = AVERROR(EINVAL);
        goto fail;
    }
    av_strlcpy(buf, mod_buf, buf_len);

    proto = avio_find_protocol_name(orig_buf_dup);
    dir = av_dirname(orig_buf_dup);

    /* if %v is present in the file's directory, create sub-directory */
    if (av_stristr(dir, "%v") && proto && !strcmp(proto, "file")) {
        mod_buf_dup = av_strdup(buf);
        if (!mod_buf_dup) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }

        dir = av_dirname(mod_buf_dup);
        if (ff_mkdir_p(dir) == -1 && errno != EEXIST) {
            ret = AVERROR(errno);
            goto fail;
        }
    }

fail:
    av_freep(&orig_buf_dup);
    av_freep(&mod_buf_dup);
    av_freep(&mod_buf);
    return ret;
}