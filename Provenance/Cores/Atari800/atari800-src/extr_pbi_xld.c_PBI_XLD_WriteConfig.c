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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 char* xld_d_rom_filename ; 
 char* xld_v_rom_filename ; 

void PBI_XLD_WriteConfig(FILE *fp)
{
	fprintf(fp, "XLD_D_ROM=%s\n", xld_d_rom_filename);
	fprintf(fp, "XLD_V_ROM=%s\n", xld_v_rom_filename);
}