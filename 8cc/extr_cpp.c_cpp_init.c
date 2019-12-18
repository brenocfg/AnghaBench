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
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  init_keywords () ; 
 int /*<<< orphan*/  init_now () ; 
 int /*<<< orphan*/  init_predefined_macros () ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 

void cpp_init() {
    setlocale(LC_ALL, "C");
    init_keywords();
    init_now();
    init_predefined_macros();
}