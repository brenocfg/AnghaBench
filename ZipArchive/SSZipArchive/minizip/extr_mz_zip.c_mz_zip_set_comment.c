#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* comment; } ;
typedef  TYPE_1__ mz_zip ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_ALLOC (scalar_t__) ; 
 int /*<<< orphan*/  MZ_FREE (char*) ; 
 scalar_t__ MZ_MEM_ERROR ; 
 scalar_t__ MZ_OK ; 
 scalar_t__ MZ_PARAM_ERROR ; 
 scalar_t__ UINT16_MAX ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,scalar_t__) ; 

int32_t mz_zip_set_comment(void *handle, const char *comment)
{
    mz_zip *zip = (mz_zip *)handle;
    int32_t comment_size = 0;
    if (zip == NULL || comment == NULL)
        return MZ_PARAM_ERROR;
    if (zip->comment != NULL)
        MZ_FREE(zip->comment);
    comment_size = (int32_t)strlen(comment);
    if (comment_size > UINT16_MAX)
        return MZ_PARAM_ERROR;
    zip->comment = (char *)MZ_ALLOC(comment_size+1);
    if (zip->comment == NULL)
        return MZ_MEM_ERROR;
    memset(zip->comment, 0, comment_size+1);
    strncpy(zip->comment, comment, comment_size);
    return MZ_OK;
}