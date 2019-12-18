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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 char const bfd_get_symbol_leading_char (int /*<<< orphan*/ *) ; 
 char* bfd_malloc (size_t) ; 
 char* cplus_demangle (char const*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 

char *
bfd_demangle (bfd *abfd, const char *name, int options)
{
  char *res, *alloc;
  const char *pre, *suf;
  size_t pre_len;

  if (abfd != NULL
      && *name != '\0'
      && bfd_get_symbol_leading_char (abfd) == *name)
    ++name;

  /* This is a hack for better error reporting on XCOFF, PowerPC64-ELF
     or the MS PE format.  These formats have a number of leading '.'s
     on at least some symbols, so we remove all dots to avoid
     confusing the demangler.  */
  pre = name;
  while (*name == '.' || *name == '$')
    ++name;
  pre_len = name - pre;

  /* Strip off @plt and suchlike too.  */
  alloc = NULL;
  suf = strchr (name, '@');
  if (suf != NULL)
    {
      alloc = bfd_malloc (suf - name + 1);
      if (alloc == NULL)
	return NULL;
      memcpy (alloc, name, suf - name);
      alloc[suf - name] = '\0';
      name = alloc;
    }

  res = cplus_demangle (name, options);

  if (alloc != NULL)
    free (alloc);

  if (res == NULL)
    return NULL;

  /* Put back any prefix or suffix.  */
  if (pre_len != 0 || suf != NULL)
    {
      size_t len;
      size_t suf_len;
      char *final;

      len = strlen (res);
      if (suf == NULL)
	suf = res + len;
      suf_len = strlen (suf) + 1;
      final = bfd_malloc (pre_len + len + suf_len);
      if (final != NULL)
	{
	  memcpy (final, pre, pre_len);
	  memcpy (final + pre_len, res, len);
	  memcpy (final + pre_len + len, suf, suf_len);
	}
      free (res);
      res = final;
    }

  return res;
}