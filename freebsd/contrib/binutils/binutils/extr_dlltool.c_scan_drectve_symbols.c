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
typedef  int flagword ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asection ;

/* Variables and functions */
 int BSF_FUNCTION ; 
 scalar_t__ CONST_STRNEQ (char*,char*) ; 
 int /*<<< orphan*/  DRECTVE_SECTION_NAME ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ add_stdcall_alias ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_get_section_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_get_section_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int bfd_get_section_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  def_exports (char*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  inform (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* strchr (char*,char) ; 
 char* xmalloc (int) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
scan_drectve_symbols (bfd *abfd)
{
  asection * s;
  int        size;
  char *     buf;
  char *     p;
  char *     e;

  /* Look for .drectve's */
  s = bfd_get_section_by_name (abfd, DRECTVE_SECTION_NAME);

  if (s == NULL)
    return;

  size = bfd_get_section_size (s);
  buf  = xmalloc (size);

  bfd_get_section_contents (abfd, s, buf, 0, size);

  /* xgettext:c-format */
  inform (_("Sucking in info from %s section in %s"),
	  DRECTVE_SECTION_NAME, bfd_get_filename (abfd));

  /* Search for -export: strings. The exported symbols can optionally
     have type tags (eg., -export:foo,data), so handle those as well.
     Currently only data tag is supported.  */
  p = buf;
  e = buf + size;
  while (p < e)
    {
      if (p[0] == '-'
	  && CONST_STRNEQ (p, "-export:"))
	{
	  char * name;
	  char * c;
	  flagword flags = BSF_FUNCTION;

	  p += 8;
	  name = p;
	  while (p < e && *p != ',' && *p != ' ' && *p != '-')
	    p++;
	  c = xmalloc (p - name + 1);
	  memcpy (c, name, p - name);
	  c[p - name] = 0;
	  if (p < e && *p == ',')       /* found type tag.  */
	    {
	      char *tag_start = ++p;
	      while (p < e && *p != ' ' && *p != '-')
		p++;
	      if (CONST_STRNEQ (tag_start, "data"))
		flags &= ~BSF_FUNCTION;
	    }

	  /* FIXME: The 5th arg is for the `constant' field.
	     What should it be?  Not that it matters since it's not
	     currently useful.  */
	  def_exports (c, 0, -1, 0, 0, ! (flags & BSF_FUNCTION), 0);

	  if (add_stdcall_alias && strchr (c, '@'))
	    {
	      int lead_at = (*c == '@') ;
	      char *exported_name = xstrdup (c + lead_at);
	      char *atsym = strchr (exported_name, '@');
	      *atsym = '\0';
	      /* Note: stdcall alias symbols can never be data.  */
	      def_exports (exported_name, xstrdup (c), -1, 0, 0, 0, 0);
	    }
	}
      else
	p++;
    }
  free (buf);
}