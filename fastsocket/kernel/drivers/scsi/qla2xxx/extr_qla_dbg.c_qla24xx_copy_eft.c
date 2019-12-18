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
struct qla_hw_data {TYPE_1__* fw_dump; int /*<<< orphan*/  eft; } ;
struct TYPE_2__ {int /*<<< orphan*/  eft_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void *
qla24xx_copy_eft(struct qla_hw_data *ha, void *ptr)
{
	if (!ha->eft)
		return ptr;

	memcpy(ptr, ha->eft, ntohl(ha->fw_dump->eft_size));
	return ptr + ntohl(ha->fw_dump->eft_size);
}