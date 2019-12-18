#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_5__ {char* obj_attrs_vendor; } ;
struct TYPE_4__ {int /*<<< orphan*/  sh_size; int /*<<< orphan*/  bfd_section; } ;
typedef  TYPE_1__ Elf_Internal_Shdr ;

/* Variables and functions */
 int OBJ_ATTR_GNU ; 
 int OBJ_ATTR_PROC ; 
#define  Tag_File 130 
#define  Tag_Section 129 
#define  Tag_Symbol 128 
 int _bfd_elf_obj_attrs_arg_type (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  bfd_elf_add_obj_attr_compat (int /*<<< orphan*/ *,int,unsigned int,char*) ; 
 int /*<<< orphan*/  bfd_elf_add_obj_attr_int (int /*<<< orphan*/ *,int,int,unsigned int) ; 
 int /*<<< orphan*/  bfd_elf_add_obj_attr_string (int /*<<< orphan*/ *,int,int,char*) ; 
 scalar_t__ bfd_get_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_2__* get_elf_backend_data (int /*<<< orphan*/ *) ; 
 void* read_unsigned_leb128 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int strlen (char*) ; 

void
_bfd_elf_parse_attributes (bfd *abfd, Elf_Internal_Shdr * hdr)
{
  bfd_byte *contents;
  bfd_byte *p;
  bfd_vma len;
  const char *std_section;

  contents = bfd_malloc (hdr->sh_size);
  if (!contents)
    return;
  if (!bfd_get_section_contents (abfd, hdr->bfd_section, contents, 0,
				 hdr->sh_size))
    {
      free (contents);
      return;
    }
  p = contents;
  std_section = get_elf_backend_data (abfd)->obj_attrs_vendor;
  if (*(p++) == 'A')
    {
      len = hdr->sh_size - 1;
      while (len > 0)
	{
	  int namelen;
	  bfd_vma section_len;
	  int vendor;

	  section_len = bfd_get_32 (abfd, p);
	  p += 4;
	  if (section_len > len)
	    section_len = len;
	  len -= section_len;
	  namelen = strlen ((char *)p) + 1;
	  section_len -= namelen + 4;
	  if (std_section && strcmp ((char *)p, std_section) == 0)
	    vendor = OBJ_ATTR_PROC;
	  else if (strcmp ((char *)p, "gnu") == 0)
	    vendor = OBJ_ATTR_GNU;
	  else
	    {
	      /* Other vendor section.  Ignore it.  */
	      p += namelen + section_len;
	      continue;
	    }

	  p += namelen;
	  while (section_len > 0)
	    {
	      int tag;
	      unsigned int n;
	      unsigned int val;
	      bfd_vma subsection_len;
	      bfd_byte *end;

	      tag = read_unsigned_leb128 (abfd, p, &n);
	      p += n;
	      subsection_len = bfd_get_32 (abfd, p);
	      p += 4;
	      if (subsection_len > section_len)
		subsection_len = section_len;
	      section_len -= subsection_len;
	      subsection_len -= n + 4;
	      end = p + subsection_len;
	      switch (tag)
		{
		case Tag_File:
		  while (p < end)
		    {
		      int type;

		      tag = read_unsigned_leb128 (abfd, p, &n);
		      p += n;
		      type = _bfd_elf_obj_attrs_arg_type (abfd, vendor, tag);
		      switch (type)
			{
			case 3:
			  val = read_unsigned_leb128 (abfd, p, &n);
			  p += n;
			  bfd_elf_add_obj_attr_compat (abfd, vendor, val,
						       (char *)p);
			  p += strlen ((char *)p) + 1;
			  break;
			case 2:
			  bfd_elf_add_obj_attr_string (abfd, vendor, tag,
						       (char *)p);
			  p += strlen ((char *)p) + 1;
			  break;
			case 1:
			  val = read_unsigned_leb128 (abfd, p, &n);
			  p += n;
			  bfd_elf_add_obj_attr_int (abfd, vendor, tag, val);
			  break;
			default:
			  abort ();
			}
		    }
		  break;
		case Tag_Section:
		case Tag_Symbol:
		  /* Don't have anywhere convenient to attach these.
		     Fall through for now.  */
		default:
		  /* Ignore things we don't kow about.  */
		  p += subsection_len;
		  subsection_len = 0;
		  break;
		}
	    }
	}
    }
  free (contents);
}