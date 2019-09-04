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
typedef  int /*<<< orphan*/  AVFilterContext ;
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 unsigned int FF_ARRAY_ELEMS (char**) ; 
 int /*<<< orphan*/  av_freep (char**) ; 
 char* av_get_token (char const**,char*) ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*) ; 
 int eval_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,unsigned int,char**) ; 

__attribute__((used)) static int expand_function(AVFilterContext *ctx, AVBPrint *bp, char **rtext)
{
    const char *text = *rtext;
    char *argv[16] = { NULL };
    unsigned argc = 0, i;
    int ret;

    if (*text != '{') {
        av_log(ctx, AV_LOG_ERROR, "Stray %% near '%s'\n", text);
        return AVERROR(EINVAL);
    }
    text++;
    while (1) {
        if (!(argv[argc++] = av_get_token(&text, ":}"))) {
            ret = AVERROR(ENOMEM);
            goto end;
        }
        if (!*text) {
            av_log(ctx, AV_LOG_ERROR, "Unterminated %%{} near '%s'\n", *rtext);
            ret = AVERROR(EINVAL);
            goto end;
        }
        if (argc == FF_ARRAY_ELEMS(argv))
            av_freep(&argv[--argc]); /* error will be caught later */
        if (*text == '}')
            break;
        text++;
    }

    if ((ret = eval_function(ctx, bp, argv[0], argc - 1, argv + 1)) < 0)
        goto end;
    ret = 0;
    *rtext = (char *)text + 1;

end:
    for (i = 0; i < argc; i++)
        av_freep(&argv[i]);
    return ret;
}