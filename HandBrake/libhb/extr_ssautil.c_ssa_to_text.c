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
typedef  int /*<<< orphan*/  hb_subtitle_style_context_t ;

/* Variables and functions */
 char* malloc (scalar_t__) ; 
 int ssa_update_style (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static char * ssa_to_text(const char *in, int *consumed,
                          hb_subtitle_style_context_t *ctx)
{
    int markup_len = 0;
    int in_pos = 0;
    int out_pos = 0;
    char *out = malloc(strlen(in) + 1); // out will never be longer than in

    for (in_pos = 0; in[in_pos] != '\0'; in_pos++)
    {
        if ((markup_len = ssa_update_style(in + in_pos, ctx)))
        {
            *consumed = in_pos + markup_len;
            out[out_pos++] = '\0';
            return out;
        }
        // Check escape codes
        if (in[in_pos] == '\\')
        {
            in_pos++;
            switch (in[in_pos])
            {
                case '\0':
                    in_pos--;
                    break;
                case 'N':
                case 'n':
                    out[out_pos++] = '\n';
                    break;
                case 'h':
                    out[out_pos++] = ' ';
                    break;
                default:
                    out[out_pos++] = in[in_pos];
                    break;
            }
        }
        else
        {
            out[out_pos++] = in[in_pos];
        }
    }
    *consumed = in_pos;
    out[out_pos++] = '\0';
    return out;
}