#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {void* num_of_file; void* pos_in_zip_directory; } ;
typedef  TYPE_1__ unz_file_pos ;
typedef  scalar_t__ unzFile ;
typedef  void* uint32_t ;
struct TYPE_5__ {scalar_t__ entry_index; } ;
typedef  TYPE_2__ mz_compat ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int MZ_OK ; 
 int UNZ_PARAMERROR ; 
 scalar_t__ unzGetOffset (scalar_t__) ; 

int unzGetFilePos(unzFile file, unz_file_pos *file_pos)
{
    mz_compat *compat = (mz_compat *)file;
    int32_t offset = 0;
    
    if (compat == NULL || file_pos == NULL)
        return UNZ_PARAMERROR;
    
    offset = unzGetOffset(file);
    if (offset < 0)
        return offset;
    
    file_pos->pos_in_zip_directory = (uint32_t)offset;
    file_pos->num_of_file = (uint32_t)compat->entry_index;
    return MZ_OK;
}