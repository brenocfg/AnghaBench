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
 int /*<<< orphan*/  g_cpu_ir ; 
 int /*<<< orphan*/  g_dasm_str ; 
 char* get_ea_mode_str_16 (int /*<<< orphan*/ ) ; 
 int read_imm_16 () ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void d68000_movem_er_16(void)
{
	uint data = read_imm_16();
	char buffer[40];
	uint first;
	uint run_length;
	uint i;

	buffer[0] = 0;
	for(i=0;i<8;i++)
	{
		if(data&(1<<i))
		{
			first = i;
			run_length = 0;
			while(i<7 && (data&(1<<(i+1))))
			{
				i++;
				run_length++;
			}
			if(buffer[0] != 0)
				strcat(buffer, "/");
			sprintf(buffer+strlen(buffer), "D%d", first);
			if(run_length > 0)
				sprintf(buffer+strlen(buffer), "-D%d", first + run_length);
		}
	}
	for(i=0;i<8;i++)
	{
		if(data&(1<<(i+8)))
		{
			first = i;
			run_length = 0;
			while(i<7 && (data&(1<<(i+8+1))))
			{
				i++;
				run_length++;
			}
			if(buffer[0] != 0)
				strcat(buffer, "/");
			sprintf(buffer+strlen(buffer), "A%d", first);
			if(run_length > 0)
				sprintf(buffer+strlen(buffer), "-A%d", first + run_length);
		}
	}
	sprintf(g_dasm_str, "movem.w %s, %s", get_ea_mode_str_16(g_cpu_ir), buffer);
}