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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  HB_RGB_TO_BGR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_rgb_lookup_by_name (char*) ; 
 char* hb_strdup_printf (char*,...) ; 
 int sscanf (char*,char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strtol (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char* srt_markup_to_ssa(char *srt, int *len)
{
    char terminator;
    char color[40];
    uint32_t rgb;

    *len = 0;
    if (srt[0] != '<' && srt[0] != '{')
        return NULL;

    if (srt[0] == '<')
        terminator = '>';
    else
        terminator = '}';

    if (srt[1] == 'i' && srt[2] == terminator)
    {
        *len = 3;
        return hb_strdup_printf("{\\i1}");
    }
    else if (srt[1] == 'b' && srt[2] == terminator)
    {
        *len = 3;
        return hb_strdup_printf("{\\b1}");
    }
    else if (srt[1] == 'u' && srt[2] == terminator)
    {
        *len = 3;
        return hb_strdup_printf("{\\u1}");
    }
    else if (srt[1] == '/' && srt[2] == 'i' && srt[3] == terminator)
    {
        *len = 4;
        return hb_strdup_printf("{\\i0}");
    }
    else if (srt[1] == '/' && srt[2] == 'b' && srt[3] == terminator)
    {
        *len = 4;
        return hb_strdup_printf("{\\b0}");
    }
    else if (srt[1] == '/' && srt[2] == 'u' && srt[3] == terminator)
    {
        *len = 4;
        return hb_strdup_printf("{\\u0}");
    }
    else if (srt[0] == '<' && !strncmp(srt + 1, "font", 4))
    {
        int match;
        match = sscanf(srt + 1, "font color=\"%39[^\"]\">", color);
        if (match != 1)
        {
            return NULL;
        }
        while (srt[*len] != '>') (*len)++;
        (*len)++;
        if (color[0] == '#')
            rgb = strtol(color + 1, NULL, 16);
        else
            rgb = hb_rgb_lookup_by_name(color);
        return hb_strdup_printf("{\\1c&H%X&}", HB_RGB_TO_BGR(rgb));
    }
    else if (srt[0] == '<' && srt[1] == '/' && !strncmp(srt + 2, "font", 4) &&
             srt[6] == '>')
    {
        *len = 7;
        return hb_strdup_printf("{\\1c&HFFFFFF&}");
    }

    return NULL;
}