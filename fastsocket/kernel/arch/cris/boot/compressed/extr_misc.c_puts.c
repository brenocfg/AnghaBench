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
 int* R_SERIAL0_STATUS ; 
 int /*<<< orphan*/ * R_SERIAL0_TR_DATA ; 
 int* R_SERIAL1_STATUS ; 
 int /*<<< orphan*/ * R_SERIAL1_TR_DATA ; 
 int* R_SERIAL2_STATUS ; 
 int /*<<< orphan*/ * R_SERIAL2_TR_DATA ; 
 int* R_SERIAL3_STATUS ; 
 int /*<<< orphan*/ * R_SERIAL3_TR_DATA ; 
 int /*<<< orphan*/  regi_ser0 ; 
 int /*<<< orphan*/  regi_ser1 ; 
 int /*<<< orphan*/  regi_ser2 ; 
 int /*<<< orphan*/  regi_ser3 ; 
 int /*<<< orphan*/  serout (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void puts(const char *s)
{
#ifndef CONFIG_ETRAX_DEBUG_PORT_NULL
	while (*s) {
#ifdef CONFIG_ETRAX_DEBUG_PORT0
#ifdef CONFIG_ETRAX_ARCH_V32
		serout(s, regi_ser0);
#else
		while (!(*R_SERIAL0_STATUS & (1 << 5)))
			;
		*R_SERIAL0_TR_DATA = *s++;
#endif
#endif
#ifdef CONFIG_ETRAX_DEBUG_PORT1
#ifdef CONFIG_ETRAX_ARCH_V32
		serout(s, regi_ser1);
#else
		while (!(*R_SERIAL1_STATUS & (1 << 5)))
			;
		*R_SERIAL1_TR_DATA = *s++;
#endif
#endif
#ifdef CONFIG_ETRAX_DEBUG_PORT2
#ifdef CONFIG_ETRAX_ARCH_V32
		serout(s, regi_ser2);
#else
		while (!(*R_SERIAL2_STATUS & (1 << 5)))
			;
		*R_SERIAL2_TR_DATA = *s++;
#endif
#endif
#ifdef CONFIG_ETRAX_DEBUG_PORT3
#ifdef CONFIG_ETRAX_ARCH_V32
		serout(s, regi_ser3);
#else
		while (!(*R_SERIAL3_STATUS & (1 << 5)))
			;
		*R_SERIAL3_TR_DATA = *s++;
#endif
#endif
		*s++;
	}
/* CONFIG_ETRAX_DEBUG_PORT_NULL */
#endif
}