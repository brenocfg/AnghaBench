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
struct TYPE_2__ {int /*<<< orphan*/  handle; scalar_t__ entry_index; } ;
typedef  TYPE_1__ mz_compat ;

/* Variables and functions */
 int UNZ_PARAMERROR ; 
 int mz_zip_goto_first_entry (int /*<<< orphan*/ ) ; 

int unzGoToFirstFile(unzFile file)
{
    mz_compat *compat = (mz_compat *)file;
    if (compat == NULL)
        return UNZ_PARAMERROR;
    compat->entry_index = 0;
    return mz_zip_goto_first_entry(compat->handle);
}