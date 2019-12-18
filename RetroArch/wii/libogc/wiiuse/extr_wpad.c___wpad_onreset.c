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
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  WPAD_Shutdown () ; 

__attribute__((used)) static s32 __wpad_onreset(s32 final)
{
	//printf("__wpad_onreset(%d)\n",final);
	if(final==FALSE) {
		WPAD_Shutdown();
	}
	return 1;
}