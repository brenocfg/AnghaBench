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
typedef  size_t uint32_t ;
struct TYPE_5__ {TYPE_1__** drv; } ;
typedef  TYPE_2__ ctlr_info_t ;
struct TYPE_4__ {int /*<<< orphan*/  LunID; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void log_unit_to_scsi3addr(ctlr_info_t *h,
	unsigned char scsi3addr[], uint32_t log_unit)
{
	memcpy(scsi3addr, h->drv[log_unit]->LunID,
		sizeof(h->drv[log_unit]->LunID));
}