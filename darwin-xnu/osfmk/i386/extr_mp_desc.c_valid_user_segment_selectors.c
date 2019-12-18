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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ valid_user_code_selector (int /*<<< orphan*/ ) ; 
 scalar_t__ valid_user_data_selector (int /*<<< orphan*/ ) ; 
 scalar_t__ valid_user_stack_selector (int /*<<< orphan*/ ) ; 

boolean_t
valid_user_segment_selectors(uint16_t cs,
		uint16_t ss,
		uint16_t ds,
		uint16_t es,
		uint16_t fs,
		uint16_t gs)
{	
	return valid_user_code_selector(cs)  &&
		valid_user_stack_selector(ss) &&
		valid_user_data_selector(ds)  &&
		valid_user_data_selector(es)  &&
		valid_user_data_selector(fs)  &&
		valid_user_data_selector(gs);
}