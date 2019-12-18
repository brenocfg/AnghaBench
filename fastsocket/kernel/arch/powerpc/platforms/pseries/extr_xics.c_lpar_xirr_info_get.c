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
 unsigned long H_SUCCESS ; 
 int /*<<< orphan*/  panic (char*,unsigned long) ; 
 unsigned long plpar_xirr (unsigned long*) ; 

__attribute__((used)) static inline unsigned int lpar_xirr_info_get(void)
{
	unsigned long lpar_rc;
	unsigned long return_value;

	lpar_rc = plpar_xirr(&return_value);
	if (lpar_rc != H_SUCCESS)
		panic(" bad return code xirr - rc = %lx \n", lpar_rc);
	return (unsigned int)return_value;
}