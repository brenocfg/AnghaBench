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
 int /*<<< orphan*/  LUA_COPYRIGHT ; 
 int /*<<< orphan*/  luai_writeline () ; 
 int /*<<< orphan*/  luai_writestring (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_version (void) {
  luai_writestring(LUA_COPYRIGHT, strlen(LUA_COPYRIGHT));
  luai_writeline();
}