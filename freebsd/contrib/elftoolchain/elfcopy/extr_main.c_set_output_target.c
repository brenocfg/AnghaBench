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
struct elfcopy {char const* otgt; void* oem; int /*<<< orphan*/  otf; int /*<<< orphan*/  oed; int /*<<< orphan*/  oec; } ;
typedef  int /*<<< orphan*/  Elftc_Bfd_Target ;

/* Variables and functions */
 int /*<<< orphan*/  ETF_EFI ; 
 int /*<<< orphan*/  ETF_ELF ; 
 int /*<<< orphan*/  ETF_PE ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/ * elftc_bfd_find_target (char const*) ; 
 int /*<<< orphan*/  elftc_bfd_target_byteorder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elftc_bfd_target_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elftc_bfd_target_flavor (int /*<<< orphan*/ *) ; 
 void* elftc_bfd_target_machine (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void
set_output_target(struct elfcopy *ecp, const char *target_name)
{
	Elftc_Bfd_Target *tgt;

	if ((tgt = elftc_bfd_find_target(target_name)) == NULL)
		errx(EXIT_FAILURE, "%s: invalid target name", target_name);
	ecp->otf = elftc_bfd_target_flavor(tgt);
	if (ecp->otf == ETF_ELF) {
		ecp->oec = elftc_bfd_target_class(tgt);
		ecp->oed = elftc_bfd_target_byteorder(tgt);
		ecp->oem = elftc_bfd_target_machine(tgt);
	}
	if (ecp->otf == ETF_EFI || ecp->otf == ETF_PE)
		ecp->oem = elftc_bfd_target_machine(tgt);

	ecp->otgt = target_name;
}