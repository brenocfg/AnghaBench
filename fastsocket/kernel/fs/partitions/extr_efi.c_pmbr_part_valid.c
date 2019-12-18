#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct partition {scalar_t__ sys_ind; int /*<<< orphan*/  start_sect; } ;

/* Variables and functions */
 scalar_t__ EFI_PMBR_OSTYPE_EFI_GPT ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
pmbr_part_valid(struct partition *part)
{
        if (part->sys_ind == EFI_PMBR_OSTYPE_EFI_GPT &&
            le32_to_cpu(part->start_sect) == 1UL)
                return 1;
        return 0;
}