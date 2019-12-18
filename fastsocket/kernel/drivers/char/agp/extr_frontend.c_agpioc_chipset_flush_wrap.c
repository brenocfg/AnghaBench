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
struct agp_file_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  agp_bridge ; 
 int /*<<< orphan*/  agp_flush_chipset (int /*<<< orphan*/ ) ; 

int agpioc_chipset_flush_wrap(struct agp_file_private *priv)
{
	DBG("");
	agp_flush_chipset(agp_bridge);
	return 0;
}