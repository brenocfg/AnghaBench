#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  l_symndx; } ;
struct internal_lineno {int /*<<< orphan*/  l_lnno; TYPE_1__ l_addr; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {int /*<<< orphan*/  l_symndx; } ;
struct TYPE_7__ {TYPE_2__ l_addr; } ;
typedef  TYPE_3__ LINENO ;

/* Variables and functions */
 int /*<<< orphan*/  GET_LINENO_LNNO (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  H_GET_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
coff_swap_lineno_in (bfd * abfd, void * ext1, void * in1)
{
  LINENO *ext = (LINENO *) ext1;
  struct internal_lineno *in = (struct internal_lineno *) in1;

  in->l_addr.l_symndx = H_GET_32 (abfd, ext->l_addr.l_symndx);
  in->l_lnno = GET_LINENO_LNNO (abfd, ext);
}