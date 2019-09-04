#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int nb_streams; TYPE_1__** streams; } ;
struct TYPE_8__ {int index; } ;
typedef  TYPE_1__ AVStream ;
typedef  TYPE_2__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,char const*) ; 
 int match_stream_specifier (TYPE_2__*,TYPE_1__*,char const*,char const**) ; 
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 

int avformat_match_stream_specifier(AVFormatContext *s, AVStream *st,
                                    const char *spec)
{
    int ret, index;
    char *endptr;
    const char *indexptr = NULL;

    ret = match_stream_specifier(s, st, spec, &indexptr);
    if (ret < 0)
        goto error;

    if (!indexptr)
        return ret;

    index = strtol(indexptr, &endptr, 0);
    if (*endptr) {                  /* We can't have anything after the requested index. */
        ret = AVERROR(EINVAL);
        goto error;
    }

    /* This is not really needed but saves us a loop for simple stream index specifiers. */
    if (spec == indexptr)
        return (index == st->index);

    /* If we requested a matching stream index, we have to ensure st is that. */
    for (int i = 0; i < s->nb_streams && index >= 0; i++) {
        ret = match_stream_specifier(s, s->streams[i], spec, NULL);
        if (ret < 0)
            goto error;
        if (ret > 0 && index-- == 0 && st == s->streams[i])
            return 1;
    }
    return 0;

error:
    if (ret == AVERROR(EINVAL))
        av_log(s, AV_LOG_ERROR, "Invalid stream specifier: %s.\n", spec);
    return ret;
}