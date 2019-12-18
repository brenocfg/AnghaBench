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
typedef  int /*<<< orphan*/  zdev_t ;
typedef  int /*<<< orphan*/  u8_t ;
struct zsRegulationTable {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regulationTable; } ;

/* Variables and functions */
 TYPE_1__* wd ; 
 int /*<<< orphan*/  zfMemoryCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zmw_get_wlan_dev (int /*<<< orphan*/ *) ; 

void zfiWlanQueryRegulationTable(zdev_t* dev, struct zsRegulationTable* pEntry)
{
    zmw_get_wlan_dev(dev);

    zfMemoryCopy((u8_t*) pEntry, (u8_t*) &wd->regulationTable,
                 sizeof(struct zsRegulationTable));
}