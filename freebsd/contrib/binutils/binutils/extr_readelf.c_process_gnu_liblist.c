#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timebuf ;
typedef  void* time_t ;
struct tm {int tm_mday; int tm_hour; int tm_min; int tm_sec; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_year; } ;
struct TYPE_12__ {unsigned int e_shnum; } ;
struct TYPE_11__ {int /*<<< orphan*/  l_flags; int /*<<< orphan*/  l_version; int /*<<< orphan*/  l_checksum; int /*<<< orphan*/  l_time_stamp; int /*<<< orphan*/  l_name; } ;
struct TYPE_10__ {size_t l_name; void* l_flags; void* l_version; void* l_checksum; } ;
struct TYPE_9__ {int sh_type; size_t sh_size; int sh_entsize; int /*<<< orphan*/  sh_offset; int /*<<< orphan*/  sh_link; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ Elf_Internal_Shdr ;
typedef  TYPE_2__ Elf32_Lib ;
typedef  TYPE_3__ Elf32_External_Lib ;

/* Variables and functions */
 void* BYTE_GET (int /*<<< orphan*/ ) ; 
 TYPE_1__* SECTION_HEADER (int /*<<< orphan*/ ) ; 
 unsigned int SECTION_HEADER_INDEX (int /*<<< orphan*/ ) ; 
 char* SECTION_NAME (TYPE_1__*) ; 
#define  SHT_GNU_LIBLIST 128 
 char* _ (char*) ; 
 int /*<<< orphan*/  do_arch ; 
 int /*<<< orphan*/  do_wide ; 
 TYPE_6__ elf_header ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 void* get_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,size_t,char*) ; 
 struct tm* gmtime (void**) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  puts (char*) ; 
 TYPE_1__* section_headers ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int
process_gnu_liblist (FILE *file)
{
  Elf_Internal_Shdr *section, *string_sec;
  Elf32_External_Lib *elib;
  char *strtab;
  size_t strtab_size;
  size_t cnt;
  unsigned i;

  if (! do_arch)
    return 0;

  for (i = 0, section = section_headers;
       i < elf_header.e_shnum;
       i++, section++)
    {
      switch (section->sh_type)
	{
	case SHT_GNU_LIBLIST:
	  if (SECTION_HEADER_INDEX (section->sh_link) >= elf_header.e_shnum)
	    break;

	  elib = get_data (NULL, file, section->sh_offset, 1, section->sh_size,
			   _("liblist"));

	  if (elib == NULL)
	    break;
	  string_sec = SECTION_HEADER (section->sh_link);

	  strtab = get_data (NULL, file, string_sec->sh_offset, 1,
			     string_sec->sh_size, _("liblist string table"));
	  strtab_size = string_sec->sh_size;

	  if (strtab == NULL
	      || section->sh_entsize != sizeof (Elf32_External_Lib))
	    {
	      free (elib);
	      break;
	    }

	  printf (_("\nLibrary list section '%s' contains %lu entries:\n"),
		  SECTION_NAME (section),
		  (long) (section->sh_size / sizeof (Elf32_External_Lib)));

	  puts ("     Library              Time Stamp          Checksum   Version Flags");

	  for (cnt = 0; cnt < section->sh_size / sizeof (Elf32_External_Lib);
	       ++cnt)
	    {
	      Elf32_Lib liblist;
	      time_t time;
	      char timebuf[20];
	      struct tm *tmp;

	      liblist.l_name = BYTE_GET (elib[cnt].l_name);
	      time = BYTE_GET (elib[cnt].l_time_stamp);
	      liblist.l_checksum = BYTE_GET (elib[cnt].l_checksum);
	      liblist.l_version = BYTE_GET (elib[cnt].l_version);
	      liblist.l_flags = BYTE_GET (elib[cnt].l_flags);

	      tmp = gmtime (&time);
	      snprintf (timebuf, sizeof (timebuf),
			"%04u-%02u-%02uT%02u:%02u:%02u",
			tmp->tm_year + 1900, tmp->tm_mon + 1, tmp->tm_mday,
			tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

	      printf ("%3lu: ", (unsigned long) cnt);
	      if (do_wide)
		printf ("%-20s", liblist.l_name < strtab_size
				 ? strtab + liblist.l_name : "<corrupt>");
	      else
		printf ("%-20.20s", liblist.l_name < strtab_size
				    ? strtab + liblist.l_name : "<corrupt>");
	      printf (" %s %#010lx %-7ld %-7ld\n", timebuf, liblist.l_checksum,
		      liblist.l_version, liblist.l_flags);
	    }

	  free (elib);
	}
    }

  return 1;
}