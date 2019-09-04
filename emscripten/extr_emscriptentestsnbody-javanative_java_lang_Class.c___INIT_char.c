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
 int /*<<< orphan*/  __TIB_char ; 
 int /*<<< orphan*/  init_primitive_class (int /*<<< orphan*/ *,char*) ; 

void __INIT_char()
{
    init_primitive_class(&__TIB_char, "char");
}