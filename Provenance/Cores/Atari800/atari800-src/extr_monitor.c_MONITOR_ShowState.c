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
typedef  int /*<<< orphan*/  UWORD ;
typedef  int UBYTE ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int ANTIC_XPOS ; 
 int ANTIC_ypos ; 
 int CPU_D_FLAG ; 
 int CPU_I_FLAG ; 
 int CPU_regP ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int,int,int,int,int,int,char,char,char,char,char,char) ; 
 int /*<<< orphan*/  show_instruction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void MONITOR_ShowState(FILE *fp, UWORD pc, UBYTE a, UBYTE x, UBYTE y, UBYTE s,
                char n, char v, char z, char c)
{
	fprintf(fp, "%3d %3d A=%02X X=%02X Y=%02X S=%02X P=%c%c*-%c%c%c%c PC=",
		ANTIC_ypos, ANTIC_XPOS, a, x, y, s,
		n, v, (CPU_regP & CPU_D_FLAG) ? 'D' : '-', (CPU_regP & CPU_I_FLAG) ? 'I' : '-', z, c);
	show_instruction(fp, pc);
}