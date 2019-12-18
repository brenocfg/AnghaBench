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
struct sdebug_host_info {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sdebug_host_info*) ; 
 struct sdebug_host_info* to_sdebug_host (struct device*) ; 

__attribute__((used)) static void sdebug_release_adapter(struct device * dev)
{
        struct sdebug_host_info *sdbg_host;

	sdbg_host = to_sdebug_host(dev);
        kfree(sdbg_host);
}