#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee_handle {int /*<<< orphan*/  vars; int /*<<< orphan*/  abfd; } ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_3__ {int flags; int index; } ;
typedef  TYPE_1__ asection ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int IEEE_SECTION_NUMBER_BASE ; 
 int SEC_CODE ; 
 int SEC_READONLY ; 
 int /*<<< orphan*/  TRUE ; 
 char* bfd_get_filename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ ieee_bb_record_enum ; 
 scalar_t__ ieee_be_record_enum ; 
 int /*<<< orphan*/  ieee_buffer_emptyp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee_change_buffer (struct ieee_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee_write_byte (struct ieee_handle*,int) ; 
 int /*<<< orphan*/  ieee_write_id (struct ieee_handle*,char*) ; 
 int /*<<< orphan*/  ieee_write_number (struct ieee_handle*,int) ; 
 void* strrchr (char const*,char) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static bfd_boolean
ieee_add_bb11 (struct ieee_handle *info, asection *sec, bfd_vma low,
	       bfd_vma high)
{
  int kind;

  if (! ieee_buffer_emptyp (&info->vars))
    {
      if (! ieee_change_buffer (info, &info->vars))
	return FALSE;
    }
  else
    {
      const char *filename, *modname;
#ifdef HAVE_DOS_BASED_FILE_SYSTEM
      const char *backslash;
#endif
      char *c, *s;

      /* Start the enclosing BB10 block.  */
      filename = bfd_get_filename (info->abfd);
      modname = strrchr (filename, '/');
#ifdef HAVE_DOS_BASED_FILE_SYSTEM
      backslash = strrchr (filename, '\\');
      if (modname == NULL || (backslash != NULL && backslash > modname))
	modname = backslash;
#endif

      if (modname != NULL)
	++modname;
#ifdef HAVE_DOS_BASED_FILE_SYSTEM
      else if (filename[0] && filename[1] == ':')
	modname = filename + 2;
#endif
      else
	modname = filename;

      c = xstrdup (modname);
      s = strrchr (c, '.');
      if (s != NULL)
	*s = '\0';

      if (! ieee_change_buffer (info, &info->vars)
	  || ! ieee_write_byte (info, (int) ieee_bb_record_enum)
	  || ! ieee_write_byte (info, 10)
	  || ! ieee_write_number (info, 0)
	  || ! ieee_write_id (info, c)
	  || ! ieee_write_id (info, "")
	  || ! ieee_write_number (info, 0)
	  || ! ieee_write_id (info, "GNU objcopy"))
	return FALSE;

      free (c);
    }

  if ((sec->flags & SEC_CODE) != 0)
    kind = 1;
  else if ((sec->flags & SEC_READONLY) != 0)
    kind = 3;
  else
    kind = 2;

  if (! ieee_write_byte (info, (int) ieee_bb_record_enum)
      || ! ieee_write_byte (info, 11)
      || ! ieee_write_number (info, 0)
      || ! ieee_write_id (info, "")
      || ! ieee_write_number (info, kind)
      || ! ieee_write_number (info, sec->index + IEEE_SECTION_NUMBER_BASE)
      || ! ieee_write_number (info, low)
      || ! ieee_write_byte (info, (int) ieee_be_record_enum)
      || ! ieee_write_number (info, high - low))
    return FALSE;

  return TRUE;
}