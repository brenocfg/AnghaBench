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
typedef  int /*<<< orphan*/  mz_zip_reader ;

/* Variables and functions */
 int /*<<< orphan*/  MZ_FREE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mz_zip_reader_close (int /*<<< orphan*/ *) ; 

void mz_zip_reader_delete(void **handle)
{
    mz_zip_reader *reader = NULL;
    if (handle == NULL)
        return;
    reader = (mz_zip_reader *)*handle;
    if (reader != NULL)
    {
        mz_zip_reader_close(reader);
        MZ_FREE(reader);
    }
    *handle = NULL;
}