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
typedef  scalar_t__ uint8_t ;
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {scalar_t__* text; int /*<<< orphan*/  textfile; } ;
typedef  TYPE_1__ DrawTextContext ;
typedef  TYPE_2__ AVFilterContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int SIZE_MAX ; 
 int av_file_map (int /*<<< orphan*/ ,scalar_t__**,size_t*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  av_file_unmap (scalar_t__*,size_t) ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__* av_realloc (scalar_t__*,size_t) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,size_t) ; 

__attribute__((used)) static int load_textfile(AVFilterContext *ctx)
{
    DrawTextContext *s = ctx->priv;
    int err;
    uint8_t *textbuf;
    uint8_t *tmp;
    size_t textbuf_size;

    if ((err = av_file_map(s->textfile, &textbuf, &textbuf_size, 0, ctx)) < 0) {
        av_log(ctx, AV_LOG_ERROR,
               "The text file '%s' could not be read or is empty\n",
               s->textfile);
        return err;
    }

    if (textbuf_size > SIZE_MAX - 1 || !(tmp = av_realloc(s->text, textbuf_size + 1))) {
        av_file_unmap(textbuf, textbuf_size);
        return AVERROR(ENOMEM);
    }
    s->text = tmp;
    memcpy(s->text, textbuf, textbuf_size);
    s->text[textbuf_size] = 0;
    av_file_unmap(textbuf, textbuf_size);

    return 0;
}