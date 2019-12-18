#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * partition_record; int /*<<< orphan*/  signature; } ;
typedef  TYPE_1__ legacy_mbr ;

/* Variables and functions */
 scalar_t__ MSDOS_MBR_SIGNATURE ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ pmbr_part_valid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
is_pmbr_valid(legacy_mbr *mbr)
{
	int i;
	if (!mbr || le16_to_cpu(mbr->signature) != MSDOS_MBR_SIGNATURE)
                return 0;
	for (i = 0; i < 4; i++)
		if (pmbr_part_valid(&mbr->partition_record[i]))
                        return 1;
	return 0;
}