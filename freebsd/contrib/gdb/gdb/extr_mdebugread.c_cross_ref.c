#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
union aux_ext {int /*<<< orphan*/  a_ti; int /*<<< orphan*/  a_rndx; } ;
struct type {int dummy; } ;
struct mdebug_pending {struct type* t; } ;
typedef  enum type_code { ____Placeholder_type_code } type_code ;
struct TYPE_18__ {int csym; int isymBase; int issBase; int iauxBase; int fBigendian; } ;
struct TYPE_17__ {int rfd; int index; } ;
struct TYPE_16__ {scalar_t__ sc; scalar_t__ st; int iss; int index; } ;
struct TYPE_15__ {scalar_t__ tq0; int bt; } ;
struct TYPE_14__ {char* ss; union aux_ext* external_aux; scalar_t__ external_sym; TYPE_4__* fdr; } ;
struct TYPE_13__ {int external_sym_size; int /*<<< orphan*/  (* swap_tir_in ) (int,int /*<<< orphan*/ *,TYPE_1__*) ;int /*<<< orphan*/  (* swap_sym_in ) (int /*<<< orphan*/ ,char*,TYPE_2__*) ;int /*<<< orphan*/  (* swap_rndx_in ) (int,int /*<<< orphan*/ *,TYPE_3__*) ;} ;
typedef  TYPE_1__ TIR ;
typedef  TYPE_2__ SYMR ;
typedef  TYPE_3__ RNDXR ;
typedef  TYPE_4__ FDR ;

/* Variables and functions */
 unsigned int AUX_GET_ISYM (int,union aux_ext*) ; 
 int /*<<< orphan*/  SC_IS_COMMON (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_FLAG_STUB ; 
 int /*<<< orphan*/  add_pending (TYPE_4__*,char*,struct type*) ; 
 int /*<<< orphan*/  bad_rfd_entry_complaint (char*,int,int) ; 
#define  btEnum 132 
#define  btStruct 131 
#define  btTypedef 130 
#define  btUnion 129 
#define  btVoid 128 
 int /*<<< orphan*/  complaint (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  cur_bfd ; 
 int /*<<< orphan*/  current_objfile ; 
 TYPE_11__* debug_info ; 
 TYPE_10__* debug_swap ; 
 TYPE_4__* get_rfd (int,unsigned int) ; 
 struct type* init_type (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 struct mdebug_pending* is_pending_symbol (TYPE_4__*,char*) ; 
 struct type* parse_type (int,union aux_ext*,int,int*,int,char*) ; 
 scalar_t__ scInfo ; 
 scalar_t__ stBlock ; 
 scalar_t__ stEnum ; 
 scalar_t__ stIndirect ; 
 scalar_t__ stStruct ; 
 scalar_t__ stTypedef ; 
 scalar_t__ stUnion ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub3 (int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  symfile_complaints ; 
 scalar_t__ tqNil ; 

__attribute__((used)) static int
cross_ref (int fd, union aux_ext *ax, struct type **tpp, enum type_code type_code,	/* Use to alloc new type if none is found. */
	   char **pname, int bigend, char *sym_name)
{
  RNDXR rn[1];
  unsigned int rf;
  int result = 1;
  FDR *fh;
  char *esh;
  SYMR sh;
  int xref_fd;
  struct mdebug_pending *pend;

  *tpp = (struct type *) NULL;

  (*debug_swap->swap_rndx_in) (bigend, &ax->a_rndx, rn);

  /* Escape index means 'the next one' */
  if (rn->rfd == 0xfff)
    {
      result++;
      rf = AUX_GET_ISYM (bigend, ax + 1);
    }
  else
    {
      rf = rn->rfd;
    }

  /* mips cc uses a rf of -1 for opaque struct definitions.
     Set TYPE_FLAG_STUB for these types so that check_typedef will
     resolve them if the struct gets defined in another compilation unit.  */
  if (rf == -1)
    {
      *pname = "<undefined>";
      *tpp = init_type (type_code, 0, TYPE_FLAG_STUB, (char *) NULL, current_objfile);
      return result;
    }

  /* mips cc uses an escaped rn->index of 0 for struct return types
     of procedures that were compiled without -g. These will always remain
     undefined.  */
  if (rn->rfd == 0xfff && rn->index == 0)
    {
      *pname = "<undefined>";
      return result;
    }

  /* Find the relative file descriptor and the symbol in it.  */
  fh = get_rfd (fd, rf);
  xref_fd = fh - debug_info->fdr;

  if (rn->index >= fh->csym)
    {
      /* File indirect entry is corrupt.  */
      *pname = "<illegal>";
      bad_rfd_entry_complaint (sym_name, xref_fd, rn->index);
      return result;
    }

  /* If we have processed this symbol then we left a forwarding
     pointer to the type in the pending list.  If not, we`ll put
     it in a list of pending types, to be processed later when
     the file will be.  In any event, we collect the name for the
     type here.  */

  esh = ((char *) debug_info->external_sym
	 + ((fh->isymBase + rn->index)
	    * debug_swap->external_sym_size));
  (*debug_swap->swap_sym_in) (cur_bfd, esh, &sh);

  /* Make sure that this type of cross reference can be handled.  */
  if ((sh.sc != scInfo
       || (sh.st != stBlock && sh.st != stTypedef && sh.st != stIndirect
	   && sh.st != stStruct && sh.st != stUnion
	   && sh.st != stEnum))
      && (sh.st != stBlock || !SC_IS_COMMON (sh.sc)))
    {
      /* File indirect entry is corrupt.  */
      *pname = "<illegal>";
      bad_rfd_entry_complaint (sym_name, xref_fd, rn->index);
      return result;
    }

  *pname = debug_info->ss + fh->issBase + sh.iss;

  pend = is_pending_symbol (fh, esh);
  if (pend)
    *tpp = pend->t;
  else
    {
      /* We have not yet seen this type.  */

      if ((sh.iss == 0 && sh.st == stTypedef) || sh.st == stIndirect)
	{
	  TIR tir;

	  /* alpha cc puts out a stTypedef with a sh.iss of zero for
	     two cases:
	     a) forward declarations of structs/unions/enums which are not
	     defined in this compilation unit.
	     For these the type will be void. This is a bad design decision
	     as cross referencing across compilation units is impossible
	     due to the missing name.
	     b) forward declarations of structs/unions/enums/typedefs which
	     are defined later in this file or in another file in the same
	     compilation unit. Irix5 cc uses a stIndirect symbol for this.
	     Simply cross reference those again to get the true type.
	     The forward references are not entered in the pending list and
	     in the symbol table.  */

	  (*debug_swap->swap_tir_in) (bigend,
				      &(debug_info->external_aux
					+ fh->iauxBase + sh.index)->a_ti,
				      &tir);
	  if (tir.tq0 != tqNil)
	    complaint (&symfile_complaints,
		       "illegal tq0 in forward typedef for %s", sym_name);
	  switch (tir.bt)
	    {
	    case btVoid:
	      *tpp = init_type (type_code, 0, 0, (char *) NULL,
				current_objfile);
	      *pname = "<undefined>";
	      break;

	    case btStruct:
	    case btUnion:
	    case btEnum:
	      cross_ref (xref_fd,
			 (debug_info->external_aux
			  + fh->iauxBase + sh.index + 1),
			 tpp, type_code, pname,
			 fh->fBigendian, sym_name);
	      break;

	    case btTypedef:
	      /* Follow a forward typedef. This might recursively
	         call cross_ref till we get a non typedef'ed type.
	         FIXME: This is not correct behaviour, but gdb currently
	         cannot handle typedefs without type copying. Type
	         copying is impossible as we might have mutual forward
	         references between two files and the copied type would not
	         get filled in when we later parse its definition.  */
	      *tpp = parse_type (xref_fd,
				 debug_info->external_aux + fh->iauxBase,
				 sh.index,
				 (int *) NULL,
				 fh->fBigendian,
				 debug_info->ss + fh->issBase + sh.iss);
	      add_pending (fh, esh, *tpp);
	      break;

	    default:
	      complaint (&symfile_complaints,
			 "illegal bt %d in forward typedef for %s", tir.bt,
			 sym_name);
	      *tpp = init_type (type_code, 0, 0, (char *) NULL,
				current_objfile);
	      break;
	    }
	  return result;
	}
      else if (sh.st == stTypedef)
	{
	  /* Parse the type for a normal typedef. This might recursively call
	     cross_ref till we get a non typedef'ed type.
	     FIXME: This is not correct behaviour, but gdb currently
	     cannot handle typedefs without type copying. But type copying is
	     impossible as we might have mutual forward references between
	     two files and the copied type would not get filled in when
	     we later parse its definition.   */
	  *tpp = parse_type (xref_fd,
			     debug_info->external_aux + fh->iauxBase,
			     sh.index,
			     (int *) NULL,
			     fh->fBigendian,
			     debug_info->ss + fh->issBase + sh.iss);
	}
      else
	{
	  /* Cross reference to a struct/union/enum which is defined
	     in another file in the same compilation unit but that file
	     has not been parsed yet.
	     Initialize the type only, it will be filled in when
	     it's definition is parsed.  */
	  *tpp = init_type (type_code, 0, 0, (char *) NULL, current_objfile);
	}
      add_pending (fh, esh, *tpp);
    }

  /* We used one auxent normally, two if we got a "next one" rf. */
  return result;
}