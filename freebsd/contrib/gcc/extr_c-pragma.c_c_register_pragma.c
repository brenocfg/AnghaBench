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
typedef  int /*<<< orphan*/  pragma_handler ;

/* Variables and functions */
 int /*<<< orphan*/  c_register_pragma_1 (char const*,char const*,int /*<<< orphan*/ ,int) ; 

void
c_register_pragma (const char *space, const char *name, pragma_handler handler)
{
  c_register_pragma_1 (space, name, handler, false);
}