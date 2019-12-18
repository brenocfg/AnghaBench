#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int mult_m68k_to_sh2; unsigned int mult_sh2_to_m68k; int is_slave; struct TYPE_7__* other_sh2; } ;
typedef  TYPE_1__ SH2 ;

/* Variables and functions */
 int /*<<< orphan*/  PDBCT_SH2 ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pdb_register_cpu (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int sh2_drc_init (TYPE_1__*) ; 

int sh2_init(SH2 *sh2, int is_slave, SH2 *other_sh2)
{
	int ret = 0;
	unsigned int mult_m68k_to_sh2 = sh2->mult_m68k_to_sh2;
	unsigned int mult_sh2_to_m68k = sh2->mult_sh2_to_m68k;

	memset(sh2, 0, sizeof(*sh2));
	sh2->is_slave = is_slave;
	sh2->other_sh2 = other_sh2;
	sh2->mult_m68k_to_sh2 = mult_m68k_to_sh2;
	sh2->mult_sh2_to_m68k = mult_sh2_to_m68k;

	pdb_register_cpu(sh2, PDBCT_SH2, is_slave ? "ssh2" : "msh2");
#ifdef DRC_SH2
	ret = sh2_drc_init(sh2);
#endif
	return ret;
}