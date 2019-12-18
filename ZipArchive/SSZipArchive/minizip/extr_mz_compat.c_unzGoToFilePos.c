#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  num_of_file; int /*<<< orphan*/  pos_in_zip_directory; } ;
typedef  TYPE_1__ unz_file_pos ;
typedef  scalar_t__ unzFile ;
struct TYPE_6__ {int /*<<< orphan*/  num_of_file; int /*<<< orphan*/  pos_in_zip_directory; } ;
typedef  TYPE_2__ unz64_file_pos ;
typedef  int /*<<< orphan*/  mz_compat ;

/* Variables and functions */
 int UNZ_PARAMERROR ; 
 int unzGoToFilePos64 (scalar_t__,TYPE_2__*) ; 

int unzGoToFilePos(unzFile file, unz_file_pos *file_pos)
{
    mz_compat *compat = (mz_compat *)file;
    unz64_file_pos file_pos64;

    if (compat == NULL || file_pos == NULL)
        return UNZ_PARAMERROR;

    file_pos64.pos_in_zip_directory = file_pos->pos_in_zip_directory;
    file_pos64.num_of_file = file_pos->num_of_file;

    return unzGoToFilePos64(file, &file_pos64);
}