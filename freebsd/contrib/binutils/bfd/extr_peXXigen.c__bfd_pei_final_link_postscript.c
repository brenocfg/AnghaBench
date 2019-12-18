#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int value; TYPE_2__* section; } ;
struct TYPE_12__ {TYPE_3__ def; } ;
struct TYPE_13__ {TYPE_4__ u; } ;
struct coff_link_hash_entry {TYPE_5__ root; } ;
struct coff_final_link_info {struct bfd_link_info* info; } ;
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_15__ {int ImageBase; TYPE_6__* DataDirectory; } ;
struct TYPE_16__ {TYPE_7__ pe_opthdr; } ;
struct TYPE_14__ {int VirtualAddress; int Size; } ;
struct TYPE_10__ {int output_offset; TYPE_1__* output_section; } ;
struct TYPE_9__ {int vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t PE_IMPORT_ADDRESS_TABLE ; 
 size_t PE_IMPORT_TABLE ; 
 size_t PE_TLS_TABLE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  coff_hash_table (struct bfd_link_info*) ; 
 struct coff_link_hash_entry* coff_link_hash_lookup (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_8__* pe_data (int /*<<< orphan*/ *) ; 

bfd_boolean
_bfd_XXi_final_link_postscript (bfd * abfd, struct coff_final_link_info *pfinfo)
{
  struct coff_link_hash_entry *h1;
  struct bfd_link_info *info = pfinfo->info;
  bfd_boolean result = TRUE;

  /* There are a few fields that need to be filled in now while we
     have symbol table access.

     The .idata subsections aren't directly available as sections, but
     they are in the symbol table, so get them from there.  */

  /* The import directory.  This is the address of .idata$2, with size
     of .idata$2 + .idata$3.  */
  h1 = coff_link_hash_lookup (coff_hash_table (info),
			      ".idata$2", FALSE, FALSE, TRUE);
  if (h1 != NULL)
    {
      /* PR ld/2729: We cannot rely upon all the output sections having been 
	 created properly, so check before referencing them.  Issue a warning
	 message for any sections tht could not be found.  */
      if (h1->root.u.def.section != NULL
	  && h1->root.u.def.section->output_section != NULL)
	pe_data (abfd)->pe_opthdr.DataDirectory[PE_IMPORT_TABLE].VirtualAddress =
	  (h1->root.u.def.value
	   + h1->root.u.def.section->output_section->vma
	   + h1->root.u.def.section->output_offset);
      else
	{
	  _bfd_error_handler
	    (_("%B: unable to fill in DataDictionary[1] because .idata$2 is missing"), 
	     abfd);
	  result = FALSE;
	}

      h1 = coff_link_hash_lookup (coff_hash_table (info),
				  ".idata$4", FALSE, FALSE, TRUE);
      if (h1 != NULL
	  && h1->root.u.def.section != NULL
	  && h1->root.u.def.section->output_section != NULL)
	pe_data (abfd)->pe_opthdr.DataDirectory[PE_IMPORT_TABLE].Size =
	  ((h1->root.u.def.value
	    + h1->root.u.def.section->output_section->vma
	    + h1->root.u.def.section->output_offset)
	   - pe_data (abfd)->pe_opthdr.DataDirectory[PE_IMPORT_TABLE].VirtualAddress);
      else
	{
	  _bfd_error_handler
	    (_("%B: unable to fill in DataDictionary[1] because .idata$4 is missing"), 
	     abfd);
	  result = FALSE;
	}

      /* The import address table.  This is the size/address of
         .idata$5.  */
      h1 = coff_link_hash_lookup (coff_hash_table (info),
				  ".idata$5", FALSE, FALSE, TRUE);
      if (h1 != NULL
	  && h1->root.u.def.section != NULL
	  && h1->root.u.def.section->output_section != NULL)
	pe_data (abfd)->pe_opthdr.DataDirectory[PE_IMPORT_ADDRESS_TABLE].VirtualAddress =
	  (h1->root.u.def.value
	   + h1->root.u.def.section->output_section->vma
	   + h1->root.u.def.section->output_offset);
      else
	{
	  _bfd_error_handler
	    (_("%B: unable to fill in DataDictionary[12] because .idata$5 is missing"), 
	     abfd);
	  result = FALSE;
	}

      h1 = coff_link_hash_lookup (coff_hash_table (info),
				  ".idata$6", FALSE, FALSE, TRUE);
      if (h1 != NULL
	  && h1->root.u.def.section != NULL
	  && h1->root.u.def.section->output_section != NULL)
	pe_data (abfd)->pe_opthdr.DataDirectory[PE_IMPORT_ADDRESS_TABLE].Size =
	  ((h1->root.u.def.value
	    + h1->root.u.def.section->output_section->vma
	    + h1->root.u.def.section->output_offset)
	   - pe_data (abfd)->pe_opthdr.DataDirectory[PE_IMPORT_ADDRESS_TABLE].VirtualAddress);      
      else
	{
	  _bfd_error_handler
	    (_("%B: unable to fill in DataDictionary[PE_IMPORT_ADDRESS_TABLE (12)] because .idata$6 is missing"), 
	     abfd);
	  result = FALSE;
	}
    }

  h1 = coff_link_hash_lookup (coff_hash_table (info),
			      "__tls_used", FALSE, FALSE, TRUE);
  if (h1 != NULL)
    {
      if (h1->root.u.def.section != NULL
	  && h1->root.u.def.section->output_section != NULL)
	pe_data (abfd)->pe_opthdr.DataDirectory[PE_TLS_TABLE].VirtualAddress =
	  (h1->root.u.def.value
	   + h1->root.u.def.section->output_section->vma
	   + h1->root.u.def.section->output_offset
	   - pe_data (abfd)->pe_opthdr.ImageBase);
      else
	{
	  _bfd_error_handler
	    (_("%B: unable to fill in DataDictionary[9] because __tls_used is missing"), 
	     abfd);
	  result = FALSE;
	}

      pe_data (abfd)->pe_opthdr.DataDirectory[PE_TLS_TABLE].Size = 0x18;
    }

  /* If we couldn't find idata$2, we either have an excessively
     trivial program or are in DEEP trouble; we have to assume trivial
     program....  */
  return result;
}