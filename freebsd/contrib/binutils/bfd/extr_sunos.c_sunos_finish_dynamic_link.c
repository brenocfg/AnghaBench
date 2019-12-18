#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct external_sun4_dynamic_link {struct external_sun4_dynamic_link* ld_text; struct external_sun4_dynamic_link* ld_symb_size; struct external_sun4_dynamic_link* ld_symbols; struct external_sun4_dynamic_link* ld_buckets; struct external_sun4_dynamic_link* ld_stab_hash; struct external_sun4_dynamic_link* ld_stab; struct external_sun4_dynamic_link* ld_hash; struct external_sun4_dynamic_link* ld_rel; struct external_sun4_dynamic_link* ld_plt_sz; struct external_sun4_dynamic_link* ld_plt; struct external_sun4_dynamic_link* ld_got; struct external_sun4_dynamic_link* ld_rules; struct external_sun4_dynamic_link* ld_need; struct external_sun4_dynamic_link* ld_loaded; struct external_sun4_dynamic_link* ld; struct external_sun4_dynamic_link* ldd; struct external_sun4_dynamic_link* ld_version; } ;
struct external_sun4_dynamic {struct external_sun4_dynamic* ld_text; struct external_sun4_dynamic* ld_symb_size; struct external_sun4_dynamic* ld_symbols; struct external_sun4_dynamic* ld_buckets; struct external_sun4_dynamic* ld_stab_hash; struct external_sun4_dynamic* ld_stab; struct external_sun4_dynamic* ld_hash; struct external_sun4_dynamic* ld_rel; struct external_sun4_dynamic* ld_plt_sz; struct external_sun4_dynamic* ld_plt; struct external_sun4_dynamic* ld_got; struct external_sun4_dynamic* ld_rules; struct external_sun4_dynamic* ld_need; struct external_sun4_dynamic* ld_loaded; struct external_sun4_dynamic* ld; struct external_sun4_dynamic* ldd; struct external_sun4_dynamic* ld_version; } ;
struct bfd_link_info {scalar_t__ shared; } ;
typedef  scalar_t__ file_ptr ;
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_size_type ;
typedef  struct external_sun4_dynamic_link bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_14__ {int /*<<< orphan*/  flags; TYPE_2__* sections; } ;
typedef  TYPE_1__ bfd ;
struct TYPE_15__ {scalar_t__ size; scalar_t__ output_offset; int flags; int reloc_count; TYPE_9__* output_section; struct external_sun4_dynamic_link* contents; struct TYPE_15__* next; } ;
typedef  TYPE_2__ asection ;
struct TYPE_18__ {scalar_t__ filepos; scalar_t__ vma; TYPE_1__* owner; } ;
struct TYPE_17__ {int /*<<< orphan*/  size; } ;
struct TYPE_16__ {scalar_t__ bucketcount; TYPE_1__* dynobj; int /*<<< orphan*/  got_needed; int /*<<< orphan*/  dynamic_sections_needed; } ;

/* Variables and functions */
 scalar_t__ BFD_ALIGN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  DYNAMIC ; 
 scalar_t__ EXTERNAL_SUN4_DYNAMIC_DEBUGGER_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GET_WORD (TYPE_1__*,struct external_sun4_dynamic_link*) ; 
 int /*<<< orphan*/  PUT_WORD (TYPE_1__*,scalar_t__,struct external_sun4_dynamic_link*) ; 
 int SEC_HAS_CONTENTS ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* bfd_get_section_by_name (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  bfd_set_section_contents (TYPE_1__*,TYPE_9__*,struct external_sun4_dynamic_link*,scalar_t__,scalar_t__) ; 
 int obj_reloc_entry_size (TYPE_1__*) ; 
 TYPE_5__* obj_textsec (TYPE_1__*) ; 
 TYPE_3__* sunos_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static bfd_boolean
sunos_finish_dynamic_link (bfd *abfd, struct bfd_link_info *info)
{
  bfd *dynobj;
  asection *o;
  asection *s;
  asection *sdyn;

  if (! sunos_hash_table (info)->dynamic_sections_needed
      && ! sunos_hash_table (info)->got_needed)
    return TRUE;

  dynobj = sunos_hash_table (info)->dynobj;

  sdyn = bfd_get_section_by_name (dynobj, ".dynamic");
  BFD_ASSERT (sdyn != NULL);

  /* Finish up the .need section.  The linker emulation code filled it
     in, but with offsets from the start of the section instead of
     real addresses.  Now that we know the section location, we can
     fill in the final values.  */
  s = bfd_get_section_by_name (dynobj, ".need");
  if (s != NULL && s->size != 0)
    {
      file_ptr filepos;
      bfd_byte *p;

      filepos = s->output_section->filepos + s->output_offset;
      p = s->contents;
      while (1)
	{
	  bfd_vma val;

	  PUT_WORD (dynobj, GET_WORD (dynobj, p) + filepos, p);
	  val = GET_WORD (dynobj, p + 12);
	  if (val == 0)
	    break;
	  PUT_WORD (dynobj, val + filepos, p + 12);
	  p += 16;
	}
    }

  /* The first entry in the .got section is the address of the
     dynamic information, unless this is a shared library.  */
  s = bfd_get_section_by_name (dynobj, ".got");
  BFD_ASSERT (s != NULL);
  if (info->shared || sdyn->size == 0)
    PUT_WORD (dynobj, 0, s->contents);
  else
    PUT_WORD (dynobj, sdyn->output_section->vma + sdyn->output_offset,
	      s->contents);

  for (o = dynobj->sections; o != NULL; o = o->next)
    {
      if ((o->flags & SEC_HAS_CONTENTS) != 0
	  && o->contents != NULL)
	{
	  BFD_ASSERT (o->output_section != NULL
		      && o->output_section->owner == abfd);
	  if (! bfd_set_section_contents (abfd, o->output_section,
					  o->contents,
					  (file_ptr) o->output_offset,
					  o->size))
	    return FALSE;
	}
    }

  if (sdyn->size > 0)
    {
      struct external_sun4_dynamic esd;
      struct external_sun4_dynamic_link esdl;
      file_ptr pos;

      /* Finish up the dynamic link information.  */
      PUT_WORD (dynobj, (bfd_vma) 3, esd.ld_version);
      PUT_WORD (dynobj,
		sdyn->output_section->vma + sdyn->output_offset + sizeof esd,
		esd.ldd);
      PUT_WORD (dynobj,
		(sdyn->output_section->vma
		 + sdyn->output_offset
		 + sizeof esd
		 + EXTERNAL_SUN4_DYNAMIC_DEBUGGER_SIZE),
		esd.ld);

      if (! bfd_set_section_contents (abfd, sdyn->output_section, &esd,
				      (file_ptr) sdyn->output_offset,
				      (bfd_size_type) sizeof esd))
	return FALSE;

      PUT_WORD (dynobj, (bfd_vma) 0, esdl.ld_loaded);

      s = bfd_get_section_by_name (dynobj, ".need");
      if (s == NULL || s->size == 0)
	PUT_WORD (dynobj, (bfd_vma) 0, esdl.ld_need);
      else
	PUT_WORD (dynobj, s->output_section->filepos + s->output_offset,
		  esdl.ld_need);

      s = bfd_get_section_by_name (dynobj, ".rules");
      if (s == NULL || s->size == 0)
	PUT_WORD (dynobj, (bfd_vma) 0, esdl.ld_rules);
      else
	PUT_WORD (dynobj, s->output_section->filepos + s->output_offset,
		  esdl.ld_rules);

      s = bfd_get_section_by_name (dynobj, ".got");
      BFD_ASSERT (s != NULL);
      PUT_WORD (dynobj, s->output_section->vma + s->output_offset,
		esdl.ld_got);

      s = bfd_get_section_by_name (dynobj, ".plt");
      BFD_ASSERT (s != NULL);
      PUT_WORD (dynobj, s->output_section->vma + s->output_offset,
		esdl.ld_plt);
      PUT_WORD (dynobj, s->size, esdl.ld_plt_sz);

      s = bfd_get_section_by_name (dynobj, ".dynrel");
      BFD_ASSERT (s != NULL);
      BFD_ASSERT (s->reloc_count * obj_reloc_entry_size (dynobj)
		  == s->size);
      PUT_WORD (dynobj, s->output_section->filepos + s->output_offset,
		esdl.ld_rel);

      s = bfd_get_section_by_name (dynobj, ".hash");
      BFD_ASSERT (s != NULL);
      PUT_WORD (dynobj, s->output_section->filepos + s->output_offset,
		esdl.ld_hash);

      s = bfd_get_section_by_name (dynobj, ".dynsym");
      BFD_ASSERT (s != NULL);
      PUT_WORD (dynobj, s->output_section->filepos + s->output_offset,
		esdl.ld_stab);

      PUT_WORD (dynobj, (bfd_vma) 0, esdl.ld_stab_hash);

      PUT_WORD (dynobj, (bfd_vma) sunos_hash_table (info)->bucketcount,
		esdl.ld_buckets);

      s = bfd_get_section_by_name (dynobj, ".dynstr");
      BFD_ASSERT (s != NULL);
      PUT_WORD (dynobj, s->output_section->filepos + s->output_offset,
		esdl.ld_symbols);
      PUT_WORD (dynobj, s->size, esdl.ld_symb_size);

      /* The size of the text area is the size of the .text section
	 rounded up to a page boundary.  FIXME: Should the page size be
	 conditional on something?  */
      PUT_WORD (dynobj,
		BFD_ALIGN (obj_textsec (abfd)->size, 0x2000),
		esdl.ld_text);

      pos = sdyn->output_offset;
      pos += sizeof esd + EXTERNAL_SUN4_DYNAMIC_DEBUGGER_SIZE;
      if (! bfd_set_section_contents (abfd, sdyn->output_section, &esdl,
				      pos, (bfd_size_type) sizeof esdl))
	return FALSE;

      abfd->flags |= DYNAMIC;
    }

  return TRUE;
}