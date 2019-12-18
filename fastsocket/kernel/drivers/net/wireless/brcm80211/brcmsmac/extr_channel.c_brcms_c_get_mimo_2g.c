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
typedef  size_t u8 ;
struct locale_mimo_info {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct locale_mimo_info const**) ; 
 struct locale_mimo_info const** g_mimo_2g_table ; 

__attribute__((used)) static const struct locale_mimo_info *brcms_c_get_mimo_2g(u8 locale_idx)
{
	if (locale_idx >= ARRAY_SIZE(g_mimo_2g_table))
		return NULL;

	return g_mimo_2g_table[locale_idx];
}