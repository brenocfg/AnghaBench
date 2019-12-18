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
typedef  char u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */

__attribute__((used)) static __inline__ u32 __get_fontsize(void *buffer)
{
	u8 *ptr = (u8*)buffer;

	if(ptr[0]=='Y' && ptr[1]=='a' && ptr[2]=='y') return (((u32*)ptr)[1]);
	else return 0;
}