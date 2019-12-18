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
typedef  scalar_t__ unzFile ;
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ mz_compat ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 int UNZ_PARAMERROR ; 
 scalar_t__ mz_zip_get_comment (int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,scalar_t__) ; 

int unzGetGlobalComment(unzFile file, char *comment, uint16_t comment_size)
{
    mz_compat *compat = (mz_compat *)file;
    const char *comment_ptr = NULL;
    int32_t err = MZ_OK;

    if (comment == NULL || comment_size == 0)
        return UNZ_PARAMERROR;
    err = mz_zip_get_comment(compat->handle, &comment_ptr);
    if (err == MZ_OK)
    {
        strncpy(comment, comment_ptr, comment_size - 1);
        comment[comment_size - 1] = 0;
    }
    return err;
}