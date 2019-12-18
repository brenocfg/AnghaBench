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
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ mz_compat ;
typedef  int int32_t ;

/* Variables and functions */
 int MZ_OK ; 
 int UNZ_PARAMERROR ; 
 int mz_zip_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mz_zip_delete (int /*<<< orphan*/ *) ; 

int unzClose_MZ(unzFile file)
{
    mz_compat *compat = (mz_compat *)file;
    int32_t err = MZ_OK;

    if (compat == NULL)
        return UNZ_PARAMERROR;

    err = mz_zip_close(compat->handle);
    mz_zip_delete(&compat->handle);

    return err;
}