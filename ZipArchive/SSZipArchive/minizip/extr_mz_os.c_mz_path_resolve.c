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
typedef  int int32_t ;

/* Variables and functions */
 int MZ_INTERNAL_ERROR ; 
 int MZ_OK ; 
 int MZ_PARAM_ERROR ; 

int32_t mz_path_resolve(const char *path, char *output, int32_t max_output)
{
    const char *source = path;
    const char *check = output;
    char *target = output;

    if (max_output <= 0)
        return MZ_PARAM_ERROR;

    while (*source != 0 && max_output > 1)
    {
        check = source;
        if ((*check == '\\') || (*check == '/'))
            check += 1;

        if ((source == path) || (check != source))
        {
            /* Skip double paths */
            if ((*check == '\\') || (*check == '/'))
            {
                source += 1;
                continue;
            }
            if ((*check != 0) && (*check == '.'))
            {
                check += 1;

                /* Remove current directory . if at end of string */
                if ((*check == 0) && (source != path))
                {
                    /* Copy last slash */
                    *target = *source;
                    target += 1;
                    max_output -= 1;
                    source += (check - source);
                    continue;
                }

                /* Remove current directory . if not at end of string */
                if ((*check == 0) || (*check == '\\' || *check == '/'))
                {
                    /* Only proceed if .\ is not entire string */
                    if (check[1] != 0 || (path != source))
                    {
                        source += (check - source);
                        continue;
                    }
                }

                /* Go to parent directory .. */
                if ((*check != 0) || (*check == '.'))
                {
                    check += 1;
                    if ((*check == 0) || (*check == '\\' || *check == '/'))
                    {
                        source += (check - source);

                        /* Search backwards for previous slash */
                        if (target != output)
                        {
                            target -= 1;
                            do
                            {
                                if ((*target == '\\') || (*target == '/'))
                                    break;

                                target -= 1;
                                max_output += 1;
                            }
                            while (target > output);
                        }

                        if ((target == output) && (*source != 0))
                            source += 1;
                        if ((*target == '\\' || *target == '/') && (*source == 0))
                            target += 1;

                        *target = 0;
                        continue;
                    }
                }
            }
        }

        *target = *source;

        source += 1;
        target += 1;
        max_output -= 1;
    }

    *target = 0;

    if (*path == 0)
        return MZ_INTERNAL_ERROR;

    return MZ_OK;
}