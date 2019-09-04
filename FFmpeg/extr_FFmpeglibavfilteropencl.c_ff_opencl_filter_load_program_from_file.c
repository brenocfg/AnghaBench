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
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int av_reallocp (char**,size_t) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int ff_opencl_filter_load_program (int /*<<< orphan*/ *,char const**,int) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int snprintf (char*,size_t,char*,char const*) ; 

int ff_opencl_filter_load_program_from_file(AVFilterContext *avctx,
                                            const char *filename)
{
    FILE *file;
    char *src = NULL;
    size_t pos, len, rb;
    const char *src_const;
    int err;

    file = fopen(filename, "r");
    if (!file) {
        av_log(avctx, AV_LOG_ERROR, "Unable to open program "
               "source file \"%s\".\n", filename);
        return AVERROR(ENOENT);
    }

    len = 1 << 16;
    pos = 0;

    err = av_reallocp(&src, len);
    if (err < 0)
        goto fail;

    err = snprintf(src, len, "#line 1 \"%s\"\n", filename);
    if (err < 0) {
        err = AVERROR(errno);
        goto fail;
    }
    if (err > len / 2) {
        err = AVERROR(EINVAL);
        goto fail;
    }
    pos = err;

    while (1) {
        rb = fread(src + pos, 1, len - pos - 1, file);
        if (rb == 0 && ferror(file)) {
            err = AVERROR(EIO);
            goto fail;
        }
        pos += rb;
        if (pos < len)
            break;
        len <<= 1;
        err = av_reallocp(&src, len);
        if (err < 0)
            goto fail;
    }
    src[pos] = 0;

    src_const = src;

    err = ff_opencl_filter_load_program(avctx, &src_const, 1);
fail:
    fclose(file);
    av_freep(&src);
    return err;
}