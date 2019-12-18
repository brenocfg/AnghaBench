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

/* Variables and functions */
 char* FAKE_LABEL_NAME ; 
 int /*<<< orphan*/  colon (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* input_line_pointer ; 
 int /*<<< orphan*/  s_stab (char) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 char* xmalloc (int) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static void
generate_asm_file (int type, char *file)
{
  static char *last_file;
  static int label_count;
  char *hold;
  char sym[30];
  char *buf;
  char *tmp = file;
  char *endp = file + strlen (file);
  char *bufp;

  if (last_file != NULL
      && strcmp (last_file, file) == 0)
    return;

  /* Rather than try to do this in some efficient fashion, we just
     generate a string and then parse it again.  That lets us use the
     existing stabs hook, which expect to see a string, rather than
     inventing new ones.  */
  hold = input_line_pointer;

  sprintf (sym, "%sF%d", FAKE_LABEL_NAME, label_count);
  ++label_count;

  /* Allocate enough space for the file name (possibly extended with
     doubled up backslashes), the symbol name, and the other characters
     that make up a stabs file directive.  */
  bufp = buf = xmalloc (2 * strlen (file) + strlen (sym) + 12);

  *bufp++ = '"';

  while (tmp < endp)
    {
      char *bslash = strchr (tmp, '\\');
      size_t len = (bslash) ? (size_t) (bslash - tmp + 1) : strlen (tmp);

      /* Double all backslashes, since demand_copy_C_string (used by
	 s_stab to extract the part in quotes) will try to replace them as
	 escape sequences.  backslash may appear in a filespec.  */
      strncpy (bufp, tmp, len);

      tmp += len;
      bufp += len;

      if (bslash != NULL)
	*bufp++ = '\\';
    }

  sprintf (bufp, "\",%d,0,0,%s\n", type, sym);

  input_line_pointer = buf;
  s_stab ('s');
  colon (sym);

  if (last_file != NULL)
    free (last_file);
  last_file = xstrdup (file);

  free (buf);

  input_line_pointer = hold;
}