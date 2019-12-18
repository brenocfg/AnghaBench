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
 char* av_strdup (char const*) ; 
 scalar_t__ av_stristr (char const*,char*) ; 
 char* avio_find_protocol_name (char*) ; 
 scalar_t__ errno ; 
 int ff_mkdir_p (char const*) ; 
 int replace_int_data_in_filename (char**,char*,char,int) ; 
 int replace_str_data_in_filename (char**,char*,char,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int format_name(const char *buf, char **s, int index, const char *varname)
{
    const char *proto, *dir;
    char *orig_buf_dup = NULL, *mod_buf_dup = NULL;
    int ret = 0;

    orig_buf_dup = av_strdup(buf);
    if (!orig_buf_dup) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    if (!av_stristr(buf, "%v")) {
        *s = orig_buf_dup;
        return ret;
    }

    if (!varname) {
        if (replace_int_data_in_filename(s, orig_buf_dup, 'v', index) < 1) {
            ret = AVERROR(EINVAL);
            goto fail;
        }
    } else {
        if (replace_str_data_in_filename(s, orig_buf_dup, 'v', varname) < 1) {
            ret = AVERROR(EINVAL);
            goto fail;
        }
    }

    proto = avio_find_protocol_name(orig_buf_dup);
    dir = av_dirname(orig_buf_dup);

    /* if %v is present in the file's directory, create sub-directory */
    if (av_stristr(dir, "%v") && proto && !strcmp(proto, "file")) {
        mod_buf_dup = av_strdup(*s);
        dir = av_dirname(mod_buf_dup);
        if (ff_mkdir_p(dir) == -1 && errno != EEXIST) {
            ret = AVERROR(errno);
            goto fail;
        }
    }

fail:
    av_freep(&orig_buf_dup);
    av_freep(&mod_buf_dup);
    return ret;
}