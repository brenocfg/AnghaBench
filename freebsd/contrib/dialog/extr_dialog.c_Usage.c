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
 int /*<<< orphan*/  dlg_exiterr (char*,char const*) ; 
 int /*<<< orphan*/  handle_leaks () ; 

__attribute__((used)) static void
Usage(const char *msg)
{
    handle_leaks();
    dlg_exiterr("Error: %s.\nUse --help to list options.\n\n", msg);
}