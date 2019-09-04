#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int file_bufsize; scalar_t__* pattern; int /*<<< orphan*/  file_buf; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ CellAutoContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int av_file_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__* av_malloc (int) ; 
 int init_pattern_from_string (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int init_pattern_from_file(AVFilterContext *ctx)
{
    CellAutoContext *s = ctx->priv;
    int ret;

    ret = av_file_map(s->filename,
                      &s->file_buf, &s->file_bufsize, 0, ctx);
    if (ret < 0)
        return ret;

    /* create a string based on the read file */
    s->pattern = av_malloc(s->file_bufsize + 1);
    if (!s->pattern)
        return AVERROR(ENOMEM);
    memcpy(s->pattern, s->file_buf, s->file_bufsize);
    s->pattern[s->file_bufsize] = 0;

    return init_pattern_from_string(ctx);
}