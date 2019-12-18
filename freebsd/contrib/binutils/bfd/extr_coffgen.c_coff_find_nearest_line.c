#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_14__ ;
typedef  struct TYPE_25__   TYPE_13__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_11__ ;
typedef  struct TYPE_22__   TYPE_10__ ;

/* Type definitions */
struct TYPE_28__ {unsigned int x_lnno; } ;
struct TYPE_29__ {TYPE_2__ x_lnsz; } ;
struct TYPE_30__ {TYPE_3__ x_misc; } ;
union internal_auxent {TYPE_4__ x_sym; } ;
struct coff_section_tdata {unsigned int i; scalar_t__ offset; char* function; unsigned int line_base; } ;
struct TYPE_32__ {scalar_t__ _n_offset; } ;
struct TYPE_33__ {TYPE_6__ _n_n; } ;
struct TYPE_34__ {scalar_t__ n_sclass; int n_numaux; scalar_t__ n_scnum; scalar_t__ n_value; TYPE_7__ _n; } ;
struct TYPE_35__ {union internal_auxent auxent; TYPE_8__ syment; } ;
struct TYPE_22__ {TYPE_9__ u; } ;
typedef  TYPE_10__ combined_entry_type ;
struct TYPE_27__ {scalar_t__ value; char* name; } ;
struct TYPE_23__ {TYPE_10__* native; TYPE_1__ symbol; } ;
typedef  TYPE_11__ coff_symbol_type ;
struct TYPE_24__ {int raw_syment_count; TYPE_10__* raw_syments; int /*<<< orphan*/  dwarf2_find_line_info; int /*<<< orphan*/  line_info; } ;
typedef  TYPE_12__ coff_data_type ;
typedef  scalar_t__ bfd_vma ;
typedef  int bfd_size_type ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_25__ {unsigned int lineno_count; scalar_t__ used_by_bfd; int /*<<< orphan*/ * owner; TYPE_14__* lineno; } ;
typedef  TYPE_13__ asection ;
struct TYPE_31__ {scalar_t__ offset; scalar_t__ sym; } ;
struct TYPE_26__ {unsigned int line_number; TYPE_5__ u; } ;
typedef  TYPE_14__ alent ;

/* Variables and functions */
 scalar_t__ C_FILE ; 
 scalar_t__ FALSE ; 
 scalar_t__ N_DEBUG ; 
 scalar_t__ TRUE ; 
 scalar_t__ _bfd_dwarf2_find_nearest_line (int /*<<< orphan*/ *,TYPE_13__*,int /*<<< orphan*/ **,scalar_t__,char const**,char const**,unsigned int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _bfd_stab_section_find_nearest_line (int /*<<< orphan*/ *,int /*<<< orphan*/ **,TYPE_13__*,scalar_t__,scalar_t__*,char const**,char const**,unsigned int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_family_coff (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_get_section_vma (int /*<<< orphan*/ *,TYPE_13__*) ; 
 scalar_t__ bfd_zalloc (int /*<<< orphan*/ *,int) ; 
 TYPE_12__* coff_data (int /*<<< orphan*/ *) ; 
 struct coff_section_tdata* coff_section_data (int /*<<< orphan*/ *,TYPE_13__*) ; 
 TYPE_13__* coff_section_from_bfd_index (int /*<<< orphan*/ *,scalar_t__) ; 

bfd_boolean
coff_find_nearest_line (bfd *abfd,
			asection *section,
			asymbol **symbols,
			bfd_vma offset,
			const char **filename_ptr,
			const char **functionname_ptr,
			unsigned int *line_ptr)
{
  bfd_boolean found;
  unsigned int i;
  unsigned int line_base;
  coff_data_type *cof = coff_data (abfd);
  /* Run through the raw syments if available.  */
  combined_entry_type *p;
  combined_entry_type *pend;
  alent *l;
  struct coff_section_tdata *sec_data;
  bfd_size_type amt;

  /* Before looking through the symbol table, try to use a .stab
     section to find the information.  */
  if (! _bfd_stab_section_find_nearest_line (abfd, symbols, section, offset,
					     &found, filename_ptr,
					     functionname_ptr, line_ptr,
					     &coff_data(abfd)->line_info))
    return FALSE;

  if (found)
    return TRUE;

  /* Also try examining DWARF2 debugging information.  */
  if (_bfd_dwarf2_find_nearest_line (abfd, section, symbols, offset,
				     filename_ptr, functionname_ptr,
				     line_ptr, 0,
				     &coff_data(abfd)->dwarf2_find_line_info))
    return TRUE;

  *filename_ptr = 0;
  *functionname_ptr = 0;
  *line_ptr = 0;

  /* Don't try and find line numbers in a non coff file.  */
  if (!bfd_family_coff (abfd))
    return FALSE;

  if (cof == NULL)
    return FALSE;

  /* Find the first C_FILE symbol.  */
  p = cof->raw_syments;
  if (!p)
    return FALSE;

  pend = p + cof->raw_syment_count;
  while (p < pend)
    {
      if (p->u.syment.n_sclass == C_FILE)
	break;
      p += 1 + p->u.syment.n_numaux;
    }

  if (p < pend)
    {
      bfd_vma sec_vma;
      bfd_vma maxdiff;

      /* Look through the C_FILE symbols to find the best one.  */
      sec_vma = bfd_get_section_vma (abfd, section);
      *filename_ptr = (char *) p->u.syment._n._n_n._n_offset;
      maxdiff = (bfd_vma) 0 - (bfd_vma) 1;
      while (1)
	{
	  combined_entry_type *p2;

	  for (p2 = p + 1 + p->u.syment.n_numaux;
	       p2 < pend;
	       p2 += 1 + p2->u.syment.n_numaux)
	    {
	      if (p2->u.syment.n_scnum > 0
		  && (section
		      == coff_section_from_bfd_index (abfd,
						      p2->u.syment.n_scnum)))
		break;
	      if (p2->u.syment.n_sclass == C_FILE)
		{
		  p2 = pend;
		  break;
		}
	    }

	  /* We use <= MAXDIFF here so that if we get a zero length
             file, we actually use the next file entry.  */
	  if (p2 < pend
	      && offset + sec_vma >= (bfd_vma) p2->u.syment.n_value
	      && offset + sec_vma - (bfd_vma) p2->u.syment.n_value <= maxdiff)
	    {
	      *filename_ptr = (char *) p->u.syment._n._n_n._n_offset;
	      maxdiff = offset + sec_vma - p2->u.syment.n_value;
	    }

	  /* Avoid endless loops on erroneous files by ensuring that
	     we always move forward in the file.  */
	  if (p >= cof->raw_syments + p->u.syment.n_value)
	    break;

	  p = cof->raw_syments + p->u.syment.n_value;
	  if (p > pend || p->u.syment.n_sclass != C_FILE)
	    break;
	}
    }

  /* Now wander though the raw linenumbers of the section.  */
  /* If we have been called on this section before, and th. e offset we
     want is further down then we can prime the lookup loop.  */
  sec_data = coff_section_data (abfd, section);
  if (sec_data != NULL
      && sec_data->i > 0
      && offset >= sec_data->offset)
    {
      i = sec_data->i;
      *functionname_ptr = sec_data->function;
      line_base = sec_data->line_base;
    }
  else
    {
      i = 0;
      line_base = 0;
    }

  if (section->lineno != NULL)
    {
      bfd_vma last_value = 0;

      l = &section->lineno[i];

      for (; i < section->lineno_count; i++)
	{
	  if (l->line_number == 0)
	    {
	      /* Get the symbol this line number points at.  */
	      coff_symbol_type *coff = (coff_symbol_type *) (l->u.sym);
	      if (coff->symbol.value > offset)
		break;
	      *functionname_ptr = coff->symbol.name;
	      last_value = coff->symbol.value;
	      if (coff->native)
		{
		  combined_entry_type *s = coff->native;
		  s = s + 1 + s->u.syment.n_numaux;

		  /* In XCOFF a debugging symbol can follow the
		     function symbol.  */
		  if (s->u.syment.n_scnum == N_DEBUG)
		    s = s + 1 + s->u.syment.n_numaux;

		  /* S should now point to the .bf of the function.  */
		  if (s->u.syment.n_numaux)
		    {
		      /* The linenumber is stored in the auxent.  */
		      union internal_auxent *a = &((s + 1)->u.auxent);
		      line_base = a->x_sym.x_misc.x_lnsz.x_lnno;
		      *line_ptr = line_base;
		    }
		}
	    }
	  else
	    {
	      if (l->u.offset > offset)
		break;
	      *line_ptr = l->line_number + line_base - 1;
	    }
	  l++;
	}

      /* If we fell off the end of the loop, then assume that this
	 symbol has no line number info.  Otherwise, symbols with no
	 line number info get reported with the line number of the
	 last line of the last symbol which does have line number
	 info.  We use 0x100 as a slop to account for cases where the
	 last line has executable code.  */
      if (i >= section->lineno_count
	  && last_value != 0
	  && offset - last_value > 0x100)
	{
	  *functionname_ptr = NULL;
	  *line_ptr = 0;
	}
    }

  /* Cache the results for the next call.  */
  if (sec_data == NULL && section->owner == abfd)
    {
      amt = sizeof (struct coff_section_tdata);
      section->used_by_bfd = bfd_zalloc (abfd, amt);
      sec_data = (struct coff_section_tdata *) section->used_by_bfd;
    }
  if (sec_data != NULL)
    {
      sec_data->offset = offset;
      sec_data->i = i;
      sec_data->function = *functionname_ptr;
      sec_data->line_base = line_base;
    }

  return TRUE;
}