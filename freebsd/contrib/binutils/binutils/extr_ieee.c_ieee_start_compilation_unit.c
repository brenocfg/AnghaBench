#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ieee_handle {char const* filename; char* modname; unsigned int name_indx; int /*<<< orphan*/  vars; int /*<<< orphan*/  types; int /*<<< orphan*/ * ranges; int /*<<< orphan*/  linenos; int /*<<< orphan*/  cxx; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ieee_bb_record_enum ; 
 int /*<<< orphan*/  ieee_change_buffer (struct ieee_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee_finish_compilation_unit (struct ieee_handle*) ; 
 int /*<<< orphan*/  ieee_init_buffer (struct ieee_handle*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee_write_byte (struct ieee_handle*,int) ; 
 int /*<<< orphan*/  ieee_write_id (struct ieee_handle*,char*) ; 
 int /*<<< orphan*/  ieee_write_number (struct ieee_handle*,int /*<<< orphan*/ ) ; 
 void* strrchr (char const*,char) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static bfd_boolean
ieee_start_compilation_unit (void *p, const char *filename)
{
  struct ieee_handle *info = (struct ieee_handle *) p;
  const char *modname;
#ifdef HAVE_DOS_BASED_FILE_SYSTEM
  const char *backslash;
#endif
  char *c, *s;
  unsigned int nindx;

  if (info->filename != NULL)
    {
      if (! ieee_finish_compilation_unit (info))
	return FALSE;
    }

  info->filename = filename;
  modname = strrchr (filename, '/');
#ifdef HAVE_DOS_BASED_FILE_SYSTEM
  /* We could have a mixed forward/back slash case.  */
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
  info->modname = c;

  if (! ieee_init_buffer (info, &info->types)
      || ! ieee_init_buffer (info, &info->vars)
      || ! ieee_init_buffer (info, &info->cxx)
      || ! ieee_init_buffer (info, &info->linenos))
    return FALSE;
  info->ranges = NULL;

  /* Always include a BB1 and a BB3 block.  That is what the output of
     the MRI linker seems to look like.  */
  if (! ieee_change_buffer (info, &info->types)
      || ! ieee_write_byte (info, (int) ieee_bb_record_enum)
      || ! ieee_write_byte (info, 1)
      || ! ieee_write_number (info, 0)
      || ! ieee_write_id (info, info->modname))
    return FALSE;

  nindx = info->name_indx;
  ++info->name_indx;
  if (! ieee_change_buffer (info, &info->vars)
      || ! ieee_write_byte (info, (int) ieee_bb_record_enum)
      || ! ieee_write_byte (info, 3)
      || ! ieee_write_number (info, 0)
      || ! ieee_write_id (info, info->modname))
    return FALSE;

  return TRUE;
}