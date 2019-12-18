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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_EXIST_ERROR ; 
 int /*<<< orphan*/  MZ_OK ; 
 int /*<<< orphan*/  MZ_PARAM_ERROR ; 

int32_t mz_path_get_filename(const char *path, const char **filename)
{
    const char *match = NULL;

    if (path == NULL || filename == NULL)
        return MZ_PARAM_ERROR;

    *filename = NULL;

    for (match = path; *match != 0; match += 1)
    {
        if ((*match == '\\') || (*match == '/'))
            *filename = match + 1;
    }

    if (*filename == NULL)
        return MZ_EXIST_ERROR;

    return MZ_OK;
}