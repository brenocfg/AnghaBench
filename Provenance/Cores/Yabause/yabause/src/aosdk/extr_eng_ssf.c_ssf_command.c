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
typedef  int s32 ;

/* Variables and functions */
 int AO_FAIL ; 
 int AO_SUCCESS ; 
#define  COMMAND_RESTART 128 

s32 ssf_command(s32 command, s32 parameter)

{
	switch (command)
	{
		case COMMAND_RESTART:
			return AO_SUCCESS;

	}
	return AO_FAIL;
}