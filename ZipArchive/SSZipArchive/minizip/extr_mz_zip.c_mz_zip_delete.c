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
typedef  int /*<<< orphan*/  mz_zip ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_FREE (int /*<<< orphan*/ *) ; 

void mz_zip_delete(void **handle)
{
    mz_zip *zip = NULL;
    if (handle == NULL)
        return;
    zip = (mz_zip *)*handle;
    if (zip != NULL)
    {
        MZ_FREE(zip);
    }
    *handle = NULL;
}