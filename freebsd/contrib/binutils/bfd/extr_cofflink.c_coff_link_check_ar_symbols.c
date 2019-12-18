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
struct internal_syment {int n_numaux; } ;
struct bfd_link_info {TYPE_1__* callbacks; int /*<<< orphan*/  hash; scalar_t__ pei386_auto_import; } ;
struct bfd_link_hash_entry {scalar_t__ type; } ;
typedef  enum coff_symbol_classification { ____Placeholder_coff_symbol_classification } coff_symbol_classification ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  (* add_archive_element ) (struct bfd_link_info*,int /*<<< orphan*/ *,char const*) ;} ;

/* Variables and functions */
 int COFF_SYMBOL_COMMON ; 
 int COFF_SYMBOL_GLOBAL ; 
 scalar_t__ CONST_STRNEQ (char const*,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SYMNMLEN ; 
 int /*<<< orphan*/  TRUE ; 
 char* _bfd_coff_internal_syment_name (int /*<<< orphan*/ *,struct internal_syment*,char*) ; 
 int bfd_coff_classify_symbol (int /*<<< orphan*/ *,struct internal_syment*) ; 
 int /*<<< orphan*/  bfd_coff_swap_sym_in (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct internal_syment*) ; 
 int bfd_coff_symesz (int /*<<< orphan*/ *) ; 
 struct bfd_link_hash_entry* bfd_link_hash_lookup (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_link_hash_undefined ; 
 scalar_t__ obj_coff_external_syms (int /*<<< orphan*/ *) ; 
 int obj_raw_syment_count (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct bfd_link_info*,int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static bfd_boolean
coff_link_check_ar_symbols (bfd *abfd,
			    struct bfd_link_info *info,
			    bfd_boolean *pneeded)
{
  bfd_size_type symesz;
  bfd_byte *esym;
  bfd_byte *esym_end;

  *pneeded = FALSE;

  symesz = bfd_coff_symesz (abfd);
  esym = (bfd_byte *) obj_coff_external_syms (abfd);
  esym_end = esym + obj_raw_syment_count (abfd) * symesz;
  while (esym < esym_end)
    {
      struct internal_syment sym;
      enum coff_symbol_classification classification;

      bfd_coff_swap_sym_in (abfd, esym, &sym);

      classification = bfd_coff_classify_symbol (abfd, &sym);
      if (classification == COFF_SYMBOL_GLOBAL
	  || classification == COFF_SYMBOL_COMMON)
	{
	  const char *name;
	  char buf[SYMNMLEN + 1];
	  struct bfd_link_hash_entry *h;

	  /* This symbol is externally visible, and is defined by this
             object file.  */
	  name = _bfd_coff_internal_syment_name (abfd, &sym, buf);
	  if (name == NULL)
	    return FALSE;
	  h = bfd_link_hash_lookup (info->hash, name, FALSE, FALSE, TRUE);

	  /* Auto import.  */
	  if (!h
	      && info->pei386_auto_import
	      && CONST_STRNEQ (name, "__imp_"))
	    h = bfd_link_hash_lookup (info->hash, name + 6, FALSE, FALSE, TRUE);

	  /* We are only interested in symbols that are currently
	     undefined.  If a symbol is currently known to be common,
	     COFF linkers do not bring in an object file which defines
	     it.  */
	  if (h != (struct bfd_link_hash_entry *) NULL
	      && h->type == bfd_link_hash_undefined)
	    {
	      if (! (*info->callbacks->add_archive_element) (info, abfd, name))
		return FALSE;
	      *pneeded = TRUE;
	      return TRUE;
	    }
	}

      esym += (sym.n_numaux + 1) * symesz;
    }

  /* We do not need this object file.  */
  return TRUE;
}