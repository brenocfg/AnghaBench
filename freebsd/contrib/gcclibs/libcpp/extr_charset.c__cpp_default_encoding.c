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
 int /*<<< orphan*/  CODESET ; 
 int /*<<< orphan*/  LC_CTYPE ; 
 char* SOURCE_CHARSET ; 
 char* nl_langinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 

const char *
_cpp_default_encoding (void)
{
  const char *current_encoding = NULL;

  /* We disable this because the default codeset is 7-bit ASCII on
     most platforms, and this causes conversion failures on every
     file in GCC that happens to have one of the upper 128 characters
     in it -- most likely, as part of the name of a contributor.
     We should definitely recognize in-band markers of file encoding,
     like:
     - the appropriate Unicode byte-order mark (FE FF) to recognize
       UTF16 and UCS4 (in both big-endian and little-endian flavors)
       and UTF8
     - a "#i", "#d", "/ *", "//", " #p" or "#p" (for #pragma) to
       distinguish ASCII and EBCDIC.
     - now we can parse something like "#pragma GCC encoding <xyz>
       on the first line, or even Emacs/VIM's mode line tags (there's
       a problem here in that VIM uses the last line, and Emacs has
       its more elaborate "local variables" convention).
     - investigate whether Java has another common convention, which
       would be friendly to support.
     (Zack Weinberg and Paolo Bonzini, May 20th 2004)  */
#if defined (HAVE_LOCALE_H) && defined (HAVE_LANGINFO_CODESET) && 0
  setlocale (LC_CTYPE, "");
  current_encoding = nl_langinfo (CODESET);
#endif
  if (current_encoding == NULL || *current_encoding == '\0')
    current_encoding = SOURCE_CHARSET;

  return current_encoding;
}