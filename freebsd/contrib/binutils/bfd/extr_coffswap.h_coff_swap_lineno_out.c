#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  l_symndx; } ;
struct internal_lineno {int /*<<< orphan*/  l_lnno; TYPE_1__ l_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  l_symndx; } ;
struct external_lineno {TYPE_2__ l_addr; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int LINESZ ; 
 int /*<<< orphan*/  PUT_LINENO_LNNO (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct external_lineno*) ; 

__attribute__((used)) static unsigned int
coff_swap_lineno_out (bfd * abfd, void * inp, void * outp)
{
  struct internal_lineno *in = (struct internal_lineno *) inp;
  struct external_lineno *ext = (struct external_lineno *) outp;
  H_PUT_32 (abfd, in->l_addr.l_symndx, ext->l_addr.l_symndx);

  PUT_LINENO_LNNO (abfd, in->l_lnno, ext);
  return LINESZ;
}