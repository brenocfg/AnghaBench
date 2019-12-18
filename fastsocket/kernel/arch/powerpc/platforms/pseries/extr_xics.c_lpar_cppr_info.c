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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 unsigned long H_SUCCESS ; 
 int /*<<< orphan*/  panic (char*,unsigned long) ; 
 unsigned long plpar_cppr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void lpar_cppr_info(u8 value)
{
	unsigned long lpar_rc;

	lpar_rc = plpar_cppr(value);
	if (lpar_rc != H_SUCCESS)
		panic("bad return code cppr - rc = %lx\n", lpar_rc);
}