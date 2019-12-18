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
typedef  scalar_t__ rc_uint_type ;

/* Variables and functions */
 scalar_t__ CP_UTF16 ; 
 scalar_t__ ISSPACE (char const) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* initial_fn ; 
 scalar_t__ memcmp (char const*,char*,size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* rc_filename ; 
 int rc_lineno ; 
 char* rclex_tok ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 void* strchr (char const*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 int strtol (char const*,char**,int) ; 
 int suppress_cpp_data ; 
 int /*<<< orphan*/  unicode_is_valid_codepage (scalar_t__) ; 
 scalar_t__ wind_current_codepage ; 
 scalar_t__ wind_default_codepage ; 
 char* xmalloc (int) ; 

__attribute__((used)) static void
cpp_line (void)
{
  const char *s = rclex_tok;
  int line;
  char *send, *fn;
  size_t len, mlen;

  ++s;
  while (ISSPACE (*s))
    ++s;
  
  /* Check for #pragma code_page ( DEFAULT | <nr>).  */
  len = strlen (s);
  mlen = strlen ("pragma");
  if (len > mlen && memcmp (s, "pragma", mlen) == 0 && ISSPACE (s[mlen]))
    {
      const char *end;

      s += mlen + 1;
      while (ISSPACE (*s))
	++s;
      len = strlen (s);
      mlen = strlen ("code_page");
      if (len <= mlen || memcmp (s, "code_page", mlen) != 0)
	/* FIXME: We ought to issue a warning message about an unrecognised pragma.  */
	return;
      s += mlen;
      while (ISSPACE (*s))
	++s;
      if (*s != '(')
	/* FIXME: We ought to issue an error message about a malformed pragma.  */
	return;
      ++s;
      while (ISSPACE (*s))
	++s;
      if (*s == 0 || (end = strchr (s, ')')) == NULL)
	/* FIXME: We ought to issue an error message about a malformed pragma.  */
	return;
      len = (size_t) (end - s);
      fn = xmalloc (len + 1);
      if (len)
      	memcpy (fn, s, len);
      fn[len] = 0;
      while (len > 0 && (fn[len - 1] > 0 && fn[len - 1] <= 0x20))
	fn[--len] = 0;
      if (! len || (len == strlen ("DEFAULT") && strcasecmp (fn, "DEFAULT") == 0))
	wind_current_codepage = wind_default_codepage;
      else if (len > 0)
	{
	  rc_uint_type ncp;

	  if (fn[0] == '0' && (fn[1] == 'x' || fn[1] == 'X'))
	      ncp = (rc_uint_type) strtol (fn + 2, NULL, 16);
	  else
	      ncp = (rc_uint_type) strtol (fn, NULL, 10);
	  if (ncp == CP_UTF16 || ! unicode_is_valid_codepage (ncp))
	    fatal (_("invalid value specified for pragma code_page.\n"));
	  wind_current_codepage = ncp;
	}
      free (fn);
      return;
    }

  line = strtol (s, &send, 0);
  if (*send != '\0' && ! ISSPACE (*send))
    return;

  /* Subtract 1 because we are about to count the newline.  */
  rc_lineno = line - 1;

  s = send;
  while (ISSPACE (*s))
    ++s;

  if (*s != '"')
    return;

  ++s;
  send = strchr (s, '"');
  if (send == NULL)
    return;

  fn = xmalloc (send - s + 1);
  strncpy (fn, s, send - s);
  fn[send - s] = '\0';

  free (rc_filename);
  rc_filename = fn;

  if (! initial_fn)
    {
      initial_fn = xmalloc (strlen (fn) + 1);
      strcpy (initial_fn, fn);
    }

  /* Allow the initial file, regardless of name.  Suppress all other
     files if they end in ".h" (this allows included "*.rc").  */
  if (strcmp (initial_fn, fn) == 0
      || strcmp (fn + strlen (fn) - 2, ".h") != 0)
    suppress_cpp_data = 0;
  else
    suppress_cpp_data = 1;
}