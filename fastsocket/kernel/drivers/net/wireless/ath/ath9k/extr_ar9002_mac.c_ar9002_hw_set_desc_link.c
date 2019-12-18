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
struct ath_desc {int /*<<< orphan*/  ds_link; } ;

/* Variables and functions */

__attribute__((used)) static void ar9002_hw_set_desc_link(void *ds, u32 ds_link)
{
	((struct ath_desc*) ds)->ds_link = ds_link;
}