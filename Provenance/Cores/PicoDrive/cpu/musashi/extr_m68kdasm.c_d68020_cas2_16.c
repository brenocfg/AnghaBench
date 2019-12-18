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
 scalar_t__ BIT_1F (int) ; 
 scalar_t__ BIT_F (int) ; 
 int /*<<< orphan*/  LIMIT_CPU_TYPES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M68020_PLUS ; 
 int /*<<< orphan*/  g_dasm_str ; 
 int read_imm_32 () ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int,int,int,char,int,char,int) ; 

__attribute__((used)) static void d68020_cas2_16(void)
{
/* CAS2 Dc1:Dc2,Du1:Dc2:(Rn1):(Rn2)
f e d c b a 9 8 7 6 5 4 3 2 1 0
 DARn1  0 0 0  Du1  0 0 0  Dc1
 DARn2  0 0 0  Du2  0 0 0  Dc2
*/

	uint extension;
	LIMIT_CPU_TYPES(M68020_PLUS);
	extension = read_imm_32();
	sprintf(g_dasm_str, "cas2.w  D%d:D%d:D%d:D%d, (%c%d):(%c%d); (2+)",
		(extension>>16)&7, extension&7, (extension>>22)&7, (extension>>6)&7,
		BIT_1F(extension) ? 'A' : 'D', (extension>>28)&7,
		BIT_F(extension) ? 'A' : 'D', (extension>>12)&7);
}