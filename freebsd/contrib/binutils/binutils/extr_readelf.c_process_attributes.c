#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ bfd_vma ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_5__ {unsigned int e_shnum; } ;
struct TYPE_4__ {unsigned int sh_type; scalar_t__ sh_size; int /*<<< orphan*/  sh_offset; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ Elf_Internal_Shdr ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 unsigned int SHT_GNU_ATTRIBUTES ; 
 scalar_t__ TRUE ; 
 char* _ (char*) ; 
 scalar_t__ byte_get (unsigned char*,int) ; 
 unsigned char* display_gnu_attribute (unsigned char*,unsigned char* (*) (unsigned char*,int)) ; 
 TYPE_3__ elf_header ; 
 int /*<<< orphan*/  free (unsigned char*) ; 
 unsigned char* get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read_uleb128 (unsigned char*,unsigned int*) ; 
 TYPE_1__* section_headers ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int strlen (char*) ; 

__attribute__((used)) static int
process_attributes (FILE *file, const char *public_name,
		    unsigned int proc_type,
		    unsigned char *(*display_pub_attribute) (unsigned char *),
		    unsigned char *(*display_proc_gnu_attribute)
			 (unsigned char *, int))
{
  Elf_Internal_Shdr *sect;
  unsigned char *contents;
  unsigned char *p;
  unsigned char *end;
  bfd_vma section_len;
  bfd_vma len;
  unsigned i;

  /* Find the section header so that we get the size.  */
  for (i = 0, sect = section_headers;
       i < elf_header.e_shnum;
       i++, sect++)
    {
      if (sect->sh_type != proc_type && sect->sh_type != SHT_GNU_ATTRIBUTES)
	continue;

      contents = get_data (NULL, file, sect->sh_offset, 1, sect->sh_size,
			   _("attributes"));

      if (!contents)
	continue;
      p = contents;
      if (*p == 'A')
	{
	  len = sect->sh_size - 1;
	  p++;
	  while (len > 0)
	    {
	      int namelen;
	      bfd_boolean public_section;
	      bfd_boolean gnu_section;

	      section_len = byte_get (p, 4);
	      p += 4;
	      if (section_len > len)
		{
		  printf (_("ERROR: Bad section length (%d > %d)\n"),
			  (int)section_len, (int)len);
		  section_len = len;
		}
	      len -= section_len;
	      printf ("Attribute Section: %s\n", p);
	      if (public_name && strcmp ((char *)p, public_name) == 0)
		public_section = TRUE;
	      else
		public_section = FALSE;
	      if (strcmp ((char *)p, "gnu") == 0)
		gnu_section = TRUE;
	      else
		gnu_section = FALSE;
	      namelen = strlen ((char *)p) + 1;
	      p += namelen;
	      section_len -= namelen + 4;
	      while (section_len > 0)
		{
		  int tag = *(p++);
		  int val;
		  bfd_vma size;
		  size = byte_get (p, 4);
		  if (size > section_len)
		    {
		      printf (_("ERROR: Bad subsection length (%d > %d)\n"),
			      (int)size, (int)section_len);
		      size = section_len;
		    }
		  section_len -= size;
		  end = p + size - 1;
		  p += 4;
		  switch (tag)
		    {
		    case 1:
		      printf ("File Attributes\n");
		      break;
		    case 2:
		      printf ("Section Attributes:");
		      goto do_numlist;
		    case 3:
		      printf ("Symbol Attributes:");
		    do_numlist:
		      for (;;)
			{
			  unsigned int i;
			  val = read_uleb128 (p, &i);
			  p += i;
			  if (val == 0)
			    break;
			  printf (" %d", val);
			}
		      printf ("\n");
		      break;
		    default:
		      printf ("Unknown tag: %d\n", tag);
		      public_section = FALSE;
		      break;
		    }
		  if (public_section)
		    {
		      while (p < end)
			p = display_pub_attribute (p);
		    }
		  else if (gnu_section)
		    {
		      while (p < end)
			p = display_gnu_attribute (p,
						   display_proc_gnu_attribute);
		    }
		  else
		    {
		      /* ??? Do something sensible, like dump hex.  */
		      printf ("  Unknown section contexts\n");
		      p = end;
		    }
		}
	    }
	}
      else
	{
	  printf (_("Unknown format '%c'\n"), *p);
	}

      free(contents);
    }
  return 1;
}