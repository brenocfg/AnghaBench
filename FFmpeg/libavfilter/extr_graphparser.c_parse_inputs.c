#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char* name; int pad_idx; } ;
typedef  TYPE_1__ AVFilterInOut ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  WHITESPACES ; 
 int /*<<< orphan*/  append_inout (TYPE_1__**,TYPE_1__**) ; 
 int /*<<< orphan*/  av_free (char*) ; 
 TYPE_1__* av_mallocz (int) ; 
 TYPE_1__* extract_inout (char*,TYPE_1__**) ; 
 char* parse_link_name (char const**,void*) ; 
 int /*<<< orphan*/  strspn (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_inputs(const char **buf, AVFilterInOut **curr_inputs,
                        AVFilterInOut **open_outputs, void *log_ctx)
{
    AVFilterInOut *parsed_inputs = NULL;
    int pad = 0;

    while (**buf == '[') {
        char *name = parse_link_name(buf, log_ctx);
        AVFilterInOut *match;

        if (!name)
            return AVERROR(EINVAL);

        /* First check if the label is not in the open_outputs list */
        match = extract_inout(name, open_outputs);

        if (match) {
            av_free(name);
        } else {
            /* Not in the list, so add it as an input */
            if (!(match = av_mallocz(sizeof(AVFilterInOut)))) {
                av_free(name);
                return AVERROR(ENOMEM);
            }
            match->name    = name;
            match->pad_idx = pad;
        }

        append_inout(&parsed_inputs, &match);

        *buf += strspn(*buf, WHITESPACES);
        pad++;
    }

    append_inout(&parsed_inputs, curr_inputs);
    *curr_inputs = parsed_inputs;

    return pad;
}