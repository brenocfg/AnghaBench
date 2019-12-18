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
typedef  int t_key ;

/* Variables and functions */
 int KEYLENGTH ; 

__attribute__((used)) static inline int tkey_mismatch(t_key a, int offset, t_key b)
{
	t_key diff = a ^ b;
	int i = offset;

	if (!diff)
		return 0;
	while ((diff << i) >> (KEYLENGTH-1) == 0)
		i++;
	return i;
}