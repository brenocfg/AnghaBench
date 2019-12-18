#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rpdr_ext {int /*<<< orphan*/  p_irpss; int /*<<< orphan*/  p_pcreg; int /*<<< orphan*/  p_framereg; int /*<<< orphan*/  p_frameoffset; int /*<<< orphan*/  p_fregoffset; int /*<<< orphan*/  p_fregmask; int /*<<< orphan*/  p_regoffset; int /*<<< orphan*/  p_regmask; int /*<<< orphan*/  p_adr; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {int /*<<< orphan*/  irpss; int /*<<< orphan*/  pcreg; int /*<<< orphan*/  framereg; int /*<<< orphan*/  frameoffset; int /*<<< orphan*/  fregoffset; int /*<<< orphan*/  fregmask; int /*<<< orphan*/  regoffset; int /*<<< orphan*/  regmask; int /*<<< orphan*/  adr; } ;
typedef  TYPE_1__ RPDR ;

/* Variables and functions */
 int /*<<< orphan*/  H_PUT_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_PUT_S32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ecoff_swap_rpdr_out (bfd *abfd, const RPDR *in, struct rpdr_ext *ex)
{
  H_PUT_S32 (abfd, in->adr, ex->p_adr);
  H_PUT_32 (abfd, in->regmask, ex->p_regmask);
  H_PUT_32 (abfd, in->regoffset, ex->p_regoffset);
  H_PUT_32 (abfd, in->fregmask, ex->p_fregmask);
  H_PUT_32 (abfd, in->fregoffset, ex->p_fregoffset);
  H_PUT_32 (abfd, in->frameoffset, ex->p_frameoffset);

  H_PUT_16 (abfd, in->framereg, ex->p_framereg);
  H_PUT_16 (abfd, in->pcreg, ex->p_pcreg);

  H_PUT_32 (abfd, in->irpss, ex->p_irpss);
}