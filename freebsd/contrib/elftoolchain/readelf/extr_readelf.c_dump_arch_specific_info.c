#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int e_machine; } ;
struct readelf {TYPE_1__ ehdr; } ;

/* Variables and functions */
#define  EM_MIPS 129 
#define  EM_MIPS_RS3_LE 128 
 int /*<<< orphan*/  dump_attributes (struct readelf*) ; 
 int /*<<< orphan*/  dump_liblist (struct readelf*) ; 
 int /*<<< orphan*/  dump_mips_specific_info (struct readelf*) ; 

__attribute__((used)) static void
dump_arch_specific_info(struct readelf *re)
{

	dump_liblist(re);
	dump_attributes(re);

	switch (re->ehdr.e_machine) {
	case EM_MIPS:
	case EM_MIPS_RS3_LE:
		dump_mips_specific_info(re);
	default:
		break;
	}
}