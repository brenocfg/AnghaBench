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
typedef  int /*<<< orphan*/  AVBPrint ;

/* Variables and functions */
 int /*<<< orphan*/  av_bprint_chars (int /*<<< orphan*/ *,char const,int) ; 
 scalar_t__ scanbraces (char const*) ; 
 char* strchr (char const*,char const) ; 

__attribute__((used)) static void handle_open_brace(AVBPrint *dst, const char **inp, int *an, int *closing_brace_missing)
{
    const char *in = *inp;

    *an += scanbraces(in);

    if (!*closing_brace_missing) {
        if (   (*an != 1 && in[1] == '\\')
            || (in[1] && strchr("CcFfoPSsYy", in[1]) && in[2] == ':')) {
            char *bracep = strchr(in+2, '}');
            if (bracep) {
                *inp = bracep;
                return;
            } else
                *closing_brace_missing = 1;
        }
    }

    av_bprint_chars(dst, *in, 1);
}