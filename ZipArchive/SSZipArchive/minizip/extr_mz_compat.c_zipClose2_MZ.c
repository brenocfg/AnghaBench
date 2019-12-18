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
typedef  scalar_t__ zipFile ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/ * handle; } ;
typedef  TYPE_1__ mz_compat ;
typedef  int int32_t ;

/* Variables and functions */
 int MZ_OK ; 
 int ZIP_PARAMERROR ; 
 int mz_zip_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_zip_delete (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  mz_zip_set_comment (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  mz_zip_set_version_madeby (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int zipClose2_MZ(zipFile file, const char *global_comment, uint16_t version_madeby)
{
    mz_compat *compat = (mz_compat *)file;
    int32_t err = MZ_OK;

    if (compat == NULL)
        return ZIP_PARAMERROR;
    if (compat->handle == NULL)
        return err;

    if (global_comment != NULL)
        mz_zip_set_comment(compat->handle, global_comment);

    mz_zip_set_version_madeby(compat->handle, version_madeby);
    err = mz_zip_close(compat->handle);
    mz_zip_delete(&compat->handle);

    return err;
}