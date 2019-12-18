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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {int /*<<< orphan*/  (* write ) (size_t,size_t const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  DRESULT ;
typedef  size_t BYTE ;

/* Variables and functions */
 TYPE_1__** s_impls ; 
 int /*<<< orphan*/  stub1 (size_t,size_t const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

DRESULT ff_disk_write (BYTE pdrv, const BYTE* buff, DWORD sector, UINT count)
{
    return s_impls[pdrv]->write(pdrv, buff, sector, count);
}