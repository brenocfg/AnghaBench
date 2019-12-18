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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int SYS_GetFontEncoding () ; 
 int /*<<< orphan*/  __SYS_ReadROM (void*,int,int) ; 
 int /*<<< orphan*/  __get_fontsize (void*) ; 

__attribute__((used)) static u32 __read_font(void *buffer)
{
	if(SYS_GetFontEncoding()==1) __SYS_ReadROM(buffer,315392,1769216);
	else __SYS_ReadROM(buffer,12288,2084608);
	return __get_fontsize(buffer);
}