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
struct obj_ssid {int dummy; } ;
struct obj_mlmeex {int dummy; } ;
struct obj_mlme {int dummy; } ;
struct obj_key {int dummy; } ;
struct obj_frequencies {int dummy; } ;
struct obj_buffer {int dummy; } ;
struct obj_bsslist {int dummy; } ;
struct obj_bss {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 

__attribute__((used)) static inline void
__bug_on_wrong_struct_sizes(void)
{
	BUILD_BUG_ON(sizeof (struct obj_ssid) != 34);
	BUILD_BUG_ON(sizeof (struct obj_key) != 34);
	BUILD_BUG_ON(sizeof (struct obj_mlme) != 12);
	BUILD_BUG_ON(sizeof (struct obj_mlmeex) != 14);
	BUILD_BUG_ON(sizeof (struct obj_buffer) != 8);
	BUILD_BUG_ON(sizeof (struct obj_bss) != 60);
	BUILD_BUG_ON(sizeof (struct obj_bsslist) != 4);
	BUILD_BUG_ON(sizeof (struct obj_frequencies) != 2);
}