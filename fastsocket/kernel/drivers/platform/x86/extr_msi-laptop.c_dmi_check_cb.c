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
struct dmi_system_id {int /*<<< orphan*/  ident; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dmi_check_cb(const struct dmi_system_id *id)
{
        printk("msi-laptop: Identified laptop model '%s'.\n", id->ident);
        return 0;
}