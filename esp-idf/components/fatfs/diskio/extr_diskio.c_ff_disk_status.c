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
struct TYPE_2__ {int /*<<< orphan*/  (* status ) (size_t) ;} ;
typedef  int /*<<< orphan*/  DSTATUS ;
typedef  size_t BYTE ;

/* Variables and functions */
 TYPE_1__** s_impls ; 
 int /*<<< orphan*/  stub1 (size_t) ; 

DSTATUS ff_disk_status (BYTE pdrv)
{
    return s_impls[pdrv]->status(pdrv);
}