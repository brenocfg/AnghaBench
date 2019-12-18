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
typedef  enum symbol_type { ____Placeholder_symbol_type } symbol_type ;

/* Variables and functions */
 int SYM_NORMAL ; 
 int SYM_STRUCT ; 
 int SYM_TYPEDEF ; 
 int SYM_UNION ; 

__attribute__((used)) static enum symbol_type map_to_ns(enum symbol_type t)
{
	if (t == SYM_TYPEDEF)
		t = SYM_NORMAL;
	else if (t == SYM_UNION)
		t = SYM_STRUCT;
	return t;
}