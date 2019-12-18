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
 int /*<<< orphan*/  M68K_CPU_TYPE_68000 ; 
 int /*<<< orphan*/  m68k_init () ; 
 int /*<<< orphan*/  m68k_set_cpu_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int M68KMusashiInit(void) {

   m68k_init();
   m68k_set_cpu_type(M68K_CPU_TYPE_68000);

   return 0;
}