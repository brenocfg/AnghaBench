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
struct efx_nic {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char const**) ; 
 char const** txc43128_test_names ; 

__attribute__((used)) static const char *txc43128_test_name(struct efx_nic *efx, unsigned int index)
{
	if (index < ARRAY_SIZE(txc43128_test_names))
		return txc43128_test_names[index];
	return NULL;
}