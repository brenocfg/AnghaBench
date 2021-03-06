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
 int /*<<< orphan*/  default_scripting_ops ; 
 int /*<<< orphan*/ * scripting_ops ; 
 int /*<<< orphan*/  setup_perl_scripting () ; 
 int /*<<< orphan*/  setup_python_scripting () ; 

__attribute__((used)) static void setup_scripting(void)
{
	setup_perl_scripting();
	setup_python_scripting();

	scripting_ops = &default_scripting_ops;
}