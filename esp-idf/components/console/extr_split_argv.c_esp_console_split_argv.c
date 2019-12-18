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
typedef  int split_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  END_ARG () ; 
#define  SS_ARG 132 
#define  SS_ARG_ESCAPED 131 
 int SS_FLAG_ESCAPE ; 
#define  SS_QUOTED_ARG 130 
#define  SS_QUOTED_ARG_ESCAPED 129 
#define  SS_SPACE 128 

size_t esp_console_split_argv(char *line, char **argv, size_t argv_size)
{
    const int QUOTE = '"';
    const int ESCAPE = '\\';
    const int SPACE = ' ';
    split_state_t state = SS_SPACE;
    int argc = 0;
    char *next_arg_start = line;
    char *out_ptr = line;
    for (char *in_ptr = line; argc < argv_size - 1; ++in_ptr) {
        int char_in = (unsigned char) *in_ptr;
        if (char_in == 0) {
            break;
        }
        int char_out = -1;

        switch (state) {
        case SS_SPACE:
            if (char_in == SPACE) {
                /* skip space */
            } else if (char_in == QUOTE) {
                next_arg_start = out_ptr;
                state = SS_QUOTED_ARG;
            } else if (char_in == ESCAPE) {
                next_arg_start = out_ptr;
                state = SS_ARG_ESCAPED;
            } else {
                next_arg_start = out_ptr;
                state = SS_ARG;
                char_out = char_in;
            }
            break;

        case SS_QUOTED_ARG:
            if (char_in == QUOTE) {
                END_ARG();
            } else if (char_in == ESCAPE) {
                state = SS_QUOTED_ARG_ESCAPED;
            } else {
                char_out = char_in;
            }
            break;

        case SS_ARG_ESCAPED:
        case SS_QUOTED_ARG_ESCAPED:
            if (char_in == ESCAPE || char_in == QUOTE || char_in == SPACE) {
                char_out = char_in;
            } else {
                /* unrecognized escape character, skip */
            }
            state = (split_state_t) (state & (~SS_FLAG_ESCAPE));
            break;

        case SS_ARG:
            if (char_in == SPACE) {
                END_ARG();
            } else if (char_in == ESCAPE) {
                state = SS_ARG_ESCAPED;
            } else {
                char_out = char_in;
            }
            break;
        }
        /* need to output anything? */
        if (char_out >= 0) {
            *out_ptr = char_out;
            ++out_ptr;
        }
    }
    /* make sure the final argument is terminated */
    *out_ptr = 0;
    /* finalize the last argument */
    if (state != SS_SPACE && argc < argv_size - 1) {
        argv[argc++] = next_arg_start;
    }
    /* add a NULL at the end of argv */
    argv[argc] = NULL;

    return argc;
}