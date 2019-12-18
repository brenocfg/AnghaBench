#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  number_disk_with_CD; int /*<<< orphan*/  size_comment; scalar_t__ number_entry; } ;
typedef  TYPE_1__ unz_global_info64 ;
struct TYPE_7__ {int /*<<< orphan*/  number_disk_with_CD; int /*<<< orphan*/  size_comment; scalar_t__ number_entry; } ;
typedef  TYPE_2__ unz_global_info ;
typedef  scalar_t__ unzFile ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  mz_compat ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ MZ_OK ; 
 int UNZ_PARAMERROR ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unzGetGlobalInfo64 (scalar_t__,TYPE_1__*) ; 

int unzGetGlobalInfo(unzFile file, unz_global_info* pglobal_info32)
{
    mz_compat *compat = (mz_compat *)file;
    unz_global_info64 global_info64;
    int32_t err = MZ_OK;

    memset(pglobal_info32, 0, sizeof(unz_global_info));
    if (compat == NULL)
        return UNZ_PARAMERROR;

    err = unzGetGlobalInfo64(file, &global_info64);
    if (err == MZ_OK)
    {
        pglobal_info32->number_entry = (uint32_t)global_info64.number_entry;
        pglobal_info32->size_comment = global_info64.size_comment;
        pglobal_info32->number_disk_with_CD = global_info64.number_disk_with_CD;
    }
    return err;
}