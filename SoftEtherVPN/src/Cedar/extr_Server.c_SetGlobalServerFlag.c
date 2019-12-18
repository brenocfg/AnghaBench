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
typedef  size_t UINT ;

/* Variables and functions */
 size_t NUM_GLOBAL_SERVER_FLAGS ; 
 size_t* global_server_flags ; 

void SetGlobalServerFlag(UINT index, UINT value)
{
	// Validate arguments
	if (index >= NUM_GLOBAL_SERVER_FLAGS)
	{
		return;
	}

	global_server_flags[index] = value;
}