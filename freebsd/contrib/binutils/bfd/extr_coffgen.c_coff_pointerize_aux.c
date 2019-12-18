#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
struct TYPE_22__ {scalar_t__ l; TYPE_9__* p; } ;
struct TYPE_19__ {scalar_t__ l; TYPE_9__* p; } ;
struct TYPE_20__ {TYPE_2__ x_endndx; } ;
struct TYPE_21__ {TYPE_3__ x_fcn; } ;
struct TYPE_23__ {TYPE_5__ x_tagndx; TYPE_4__ x_fcnary; } ;
struct TYPE_24__ {TYPE_6__ x_sym; } ;
struct TYPE_18__ {unsigned int n_type; unsigned int n_sclass; } ;
struct TYPE_25__ {TYPE_7__ auxent; TYPE_1__ syment; } ;
struct TYPE_26__ {int fix_end; int fix_tag; TYPE_8__ u; } ;
typedef  TYPE_9__ combined_entry_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_17__ {scalar_t__ (* _bfd_coff_pointerize_aux_hook ) (int /*<<< orphan*/ *,TYPE_9__*,TYPE_9__*,unsigned int,TYPE_9__*) ;} ;

/* Variables and functions */
 unsigned int C_BLOCK ; 
 unsigned int C_FCN ; 
 unsigned int C_FILE ; 
 unsigned int C_STAT ; 
 scalar_t__ ISFCN (unsigned int) ; 
 scalar_t__ ISTAG (unsigned int) ; 
 unsigned int T_NULL ; 
 TYPE_16__* coff_backend_info (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,TYPE_9__*,TYPE_9__*,unsigned int,TYPE_9__*) ; 

__attribute__((used)) static void
coff_pointerize_aux (bfd *abfd,
		     combined_entry_type *table_base,
		     combined_entry_type *symbol,
		     unsigned int indaux,
		     combined_entry_type *auxent)
{
  unsigned int type = symbol->u.syment.n_type;
  unsigned int class = symbol->u.syment.n_sclass;

  if (coff_backend_info (abfd)->_bfd_coff_pointerize_aux_hook)
    {
      if ((*coff_backend_info (abfd)->_bfd_coff_pointerize_aux_hook)
	  (abfd, table_base, symbol, indaux, auxent))
	return;
    }

  /* Don't bother if this is a file or a section.  */
  if (class == C_STAT && type == T_NULL)
    return;
  if (class == C_FILE)
    return;

  /* Otherwise patch up.  */
#define N_TMASK coff_data  (abfd)->local_n_tmask
#define N_BTSHFT coff_data (abfd)->local_n_btshft
  
  if ((ISFCN (type) || ISTAG (class) || class == C_BLOCK || class == C_FCN)
      && auxent->u.auxent.x_sym.x_fcnary.x_fcn.x_endndx.l > 0)
    {
      auxent->u.auxent.x_sym.x_fcnary.x_fcn.x_endndx.p =
	table_base + auxent->u.auxent.x_sym.x_fcnary.x_fcn.x_endndx.l;
      auxent->fix_end = 1;
    }
  /* A negative tagndx is meaningless, but the SCO 3.2v4 cc can
     generate one, so we must be careful to ignore it.  */
  if (auxent->u.auxent.x_sym.x_tagndx.l > 0)
    {
      auxent->u.auxent.x_sym.x_tagndx.p =
	table_base + auxent->u.auxent.x_sym.x_tagndx.l;
      auxent->fix_tag = 1;
    }
}