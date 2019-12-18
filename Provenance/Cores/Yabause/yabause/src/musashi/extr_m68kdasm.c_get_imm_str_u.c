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
typedef  int uint ;

/* Variables and functions */
 int read_imm_16 () ; 
 int read_imm_32 () ; 
 int read_imm_8 () ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static char* get_imm_str_u(uint size)
{
	static char str[15];
	if(size == 0)
		sprintf(str, "#$%x", read_imm_8() & 0xff);
	else if(size == 1)
		sprintf(str, "#$%x", read_imm_16() & 0xffff);
	else
		sprintf(str, "#$%x", read_imm_32() & 0xffffffff);
	return str;
}