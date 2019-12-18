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
typedef  int /*<<< orphan*/  u32 ;
struct pm8001_hba_info {void* tags; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void pm8001_tag_set(struct pm8001_hba_info *pm8001_ha, u32 tag)
{
	void *bitmap = pm8001_ha->tags;
	set_bit(tag, bitmap);
}