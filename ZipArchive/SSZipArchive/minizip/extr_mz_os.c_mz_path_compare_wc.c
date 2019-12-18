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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_EXIST_ERROR ; 
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  tolower (char const) ; 

int32_t mz_path_compare_wc(const char *path, const char *wildcard, uint8_t ignore_case)
{
    while (*path != 0)
    {
        switch (*wildcard)
        {
        case '*':

            if (*(wildcard + 1) == 0)
                return MZ_OK;

            while (*path != 0)
            {
                if (mz_path_compare_wc(path, (wildcard + 1), ignore_case) == MZ_OK)
                    return MZ_OK;

                path += 1;
            }

            return MZ_EXIST_ERROR;

        default:
            /* Ignore differences in path slashes on platforms */
            if ((*path == '\\' && *wildcard == '/') || (*path == '/' && *wildcard == '\\'))
                break;

            if (ignore_case)
            {
                if (tolower(*path) != tolower(*wildcard))
                    return MZ_EXIST_ERROR;
            }
            else
            {
                if (*path != *wildcard)
                    return MZ_EXIST_ERROR;
            }

            break;
        }

        path += 1;
        wildcard += 1;
    }

    if ((*wildcard != 0) && (*wildcard != '*'))
        return MZ_EXIST_ERROR;

    return MZ_OK;
}