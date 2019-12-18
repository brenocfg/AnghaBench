#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* _n_offset; scalar_t__ _n_zeroes; } ;
struct TYPE_8__ {int /*<<< orphan*/  _n_name; TYPE_1__ _n_n; } ;
struct internal_syment {void* n_numaux; void* n_sclass; void* n_type; void* n_scnum; void* n_value; TYPE_3__ _n; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {int /*<<< orphan*/  e_offset; } ;
struct TYPE_9__ {scalar_t__* e_name; TYPE_2__ e; } ;
struct TYPE_10__ {int /*<<< orphan*/  e_numaux; int /*<<< orphan*/  e_sclass; int /*<<< orphan*/  e_type; int /*<<< orphan*/  e_scnum; int /*<<< orphan*/  e_value; TYPE_4__ e; } ;
typedef  TYPE_5__ SYMENT ;

/* Variables and functions */
 int /*<<< orphan*/  COFF_ADJUST_SYM_IN_POST (int /*<<< orphan*/ *,void*,void*) ; 
 void* H_GET_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* H_GET_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* H_GET_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYMNMLEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
coff_swap_sym_in (bfd * abfd, void * ext1, void * in1)
{
  SYMENT *ext = (SYMENT *) ext1;
  struct internal_syment *in = (struct internal_syment *) in1;

  if (ext->e.e_name[0] == 0)
    {
      in->_n._n_n._n_zeroes = 0;
      in->_n._n_n._n_offset = H_GET_32 (abfd, ext->e.e.e_offset);
    }
  else
    {
#if SYMNMLEN != E_SYMNMLEN
#error we need to cope with truncating or extending SYMNMLEN
#else
      memcpy (in->_n._n_name, ext->e.e_name, SYMNMLEN);
#endif
    }

  in->n_value = H_GET_32 (abfd, ext->e_value);
  in->n_scnum = H_GET_16 (abfd, ext->e_scnum);
  if (sizeof (ext->e_type) == 2)
    in->n_type = H_GET_16 (abfd, ext->e_type);
  else
    in->n_type = H_GET_32 (abfd, ext->e_type);
  in->n_sclass = H_GET_8 (abfd, ext->e_sclass);
  in->n_numaux = H_GET_8 (abfd, ext->e_numaux);
#ifdef COFF_ADJUST_SYM_IN_POST
  COFF_ADJUST_SYM_IN_POST (abfd, ext1, in1);
#endif
}