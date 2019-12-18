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
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  union aux_ext {int dummy; } aux_ext ;
struct section_offsets {int dummy; } ;
struct objfile {int dummy; } ;
struct TYPE_10__ {scalar_t__ ssext; TYPE_4__* fdr; union aux_ext* external_aux; } ;
struct TYPE_9__ {int iauxBase; } ;
struct TYPE_8__ {scalar_t__ sc; int st; scalar_t__ iss; } ;
struct TYPE_7__ {scalar_t__ ifd; TYPE_2__ asym; } ;
typedef  TYPE_1__ EXTR ;

/* Variables and functions */
 int /*<<< orphan*/  SC_IS_COMMON (scalar_t__) ; 
 scalar_t__ SC_IS_UNDEF (scalar_t__) ; 
 int cur_fd ; 
 TYPE_4__* cur_fdr ; 
 TYPE_5__* debug_info ; 
 int /*<<< orphan*/  fdr_name (TYPE_4__*) ; 
 scalar_t__ ifdNil ; 
 scalar_t__ info_verbose ; 
 int /*<<< orphan*/  n_undef_labels ; 
 int /*<<< orphan*/  n_undef_procs ; 
 int /*<<< orphan*/  n_undef_symbols ; 
 int /*<<< orphan*/  n_undef_vars ; 
 int /*<<< orphan*/  parse_symbol (TYPE_2__*,union aux_ext*,char*,int,struct section_offsets*,struct objfile*) ; 
 int /*<<< orphan*/  printf_filtered (char*,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ scNil ; 
#define  stGlobal 132 
#define  stLabel 131 
#define  stNil 130 
#define  stProc 129 
#define  stStaticProc 128 

__attribute__((used)) static void
parse_external (EXTR *es, int bigend, struct section_offsets *section_offsets,
		struct objfile *objfile)
{
  union aux_ext *ax;

  if (es->ifd != ifdNil)
    {
      cur_fd = es->ifd;
      cur_fdr = debug_info->fdr + cur_fd;
      ax = debug_info->external_aux + cur_fdr->iauxBase;
    }
  else
    {
      cur_fdr = debug_info->fdr;
      ax = 0;
    }

  /* Reading .o files */
  if (SC_IS_UNDEF (es->asym.sc) || es->asym.sc == scNil)
    {
      char *what;
      switch (es->asym.st)
	{
	case stNil:
	  /* These are generated for static symbols in .o files,
	     ignore them.  */
	  return;
	case stStaticProc:
	case stProc:
	  what = "procedure";
	  n_undef_procs++;
	  break;
	case stGlobal:
	  what = "variable";
	  n_undef_vars++;
	  break;
	case stLabel:
	  what = "label";
	  n_undef_labels++;
	  break;
	default:
	  what = "symbol";
	  break;
	}
      n_undef_symbols++;
      /* FIXME:  Turn this into a complaint? */
      if (info_verbose)
	printf_filtered ("Warning: %s `%s' is undefined (in %s)\n",
			 what, debug_info->ssext + es->asym.iss,
			 fdr_name (cur_fdr));
      return;
    }

  switch (es->asym.st)
    {
    case stProc:
    case stStaticProc:
      /* There is no need to parse the external procedure symbols.
         If they are from objects compiled without -g, their index will
         be indexNil, and the symbol definition from the minimal symbol
         is preferrable (yielding a function returning int instead of int).
         If the index points to a local procedure symbol, the local
         symbol already provides the correct type.
         Note that the index of the external procedure symbol points
         to the local procedure symbol in the local symbol table, and
         _not_ to the auxiliary symbol info.  */
      break;
    case stGlobal:
    case stLabel:
      /* Global common symbols are resolved by the runtime loader,
         ignore them.  */
      if (SC_IS_COMMON (es->asym.sc))
	break;

      /* Note that the case of a symbol with indexNil must be handled
         anyways by parse_symbol().  */
      parse_symbol (&es->asym, ax, (char *) NULL, bigend, section_offsets, objfile);
      break;
    default:
      break;
    }
}