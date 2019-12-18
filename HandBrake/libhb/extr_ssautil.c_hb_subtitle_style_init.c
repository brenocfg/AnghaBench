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
typedef  int /*<<< orphan*/  ssa_style_indicies_t ;
typedef  int /*<<< orphan*/  hb_subtitle_style_context_t ;

/* Variables and functions */
 scalar_t__ add_style (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * calloc (int,int) ; 
 int /*<<< orphan*/  fill_field_indicies (char**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char** get_fields (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hb_str_vfree (char**) ; 
 char* sgetline (char*) ; 
 int /*<<< orphan*/  ssa_style_reset (int /*<<< orphan*/ *) ; 
 char* strchr (char*,char) ; 
 char* strstr (char const*,char*) ; 

hb_subtitle_style_context_t * hb_subtitle_style_init(const char * ssa_header)
{
    hb_subtitle_style_context_t * ctx;

    ctx = calloc(1, sizeof(*ctx));
    if (ctx == NULL)
    {
        return NULL;
    }
    if (ssa_header != NULL)
    {
        // Find beginning of styles
        char *  pos = strstr(ssa_header, "[V4");

        if (pos != NULL)
        {
            pos = strstr(pos, "\nFormat:");
            if (pos != NULL)
            {
                char ** fields;
                int     next = 7;
                char  * line = sgetline(pos + 8);

                fields = get_fields(line, 0);
                free(line);

                if (fields != NULL)
                {
                    ssa_style_indicies_t field_indices;

                    fill_field_indicies(fields, &field_indices);

                    pos    = strstr(pos, "\nStyle:");
                    while (pos != NULL)
                    {
                        char ** style;

                        line = sgetline(pos + next);
                        style = get_fields(line, 0);
                        free(line);

                        if (add_style(ctx, style, &field_indices))
                        {
                            hb_str_vfree(style);
                            break;
                        }
                        pos = strchr(pos + next, '\n');
                        next = 1;

                        hb_str_vfree(style);
                    }

                    hb_str_vfree(fields);
                }
            }
        }
    }
    ssa_style_reset(ctx);
    return ctx;
}