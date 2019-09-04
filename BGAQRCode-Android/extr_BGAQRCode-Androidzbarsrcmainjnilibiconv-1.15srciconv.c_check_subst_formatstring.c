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
 int CHAR_BIT ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  c_isprint (char const) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,...) ; 
 scalar_t__ isdigit (char const) ; 
 char* ngettext (char*,char*,unsigned int) ; 

__attribute__((used)) static size_t check_subst_formatstring (const char *format, const char *param_name)
{
  /* C format strings are described in POSIX (IEEE P1003.1 2001), section
     XSH 3 fprintf().  See also Linux fprintf(3) manual page.
     For simplicity, we don't accept
       - the '%m$' reordering syntax,
       - the 'I' flag,
       - width specifications referring to an argument,
       - precision specifications referring to an argument,
       - size specifiers,
       - format specifiers other than 'o', 'u', 'x', 'X'.
     What remains?
     A directive
       - starts with '%',
       - is optionally followed by any of the characters '#', '0', '-', ' ',
         '+', "'", each of which acts as a flag,
       - is optionally followed by a width specification: a nonempty digit
         sequence,
       - is optionally followed by '.' and a precision specification: a
         nonempty digit sequence,
       - is finished by a specifier
         - '%', that needs no argument,
         - 'o', 'u', 'x', 'X', that need an unsigned integer argument.
   */
  size_t maxsize = 0;
  unsigned int unnumbered_arg_count = 0;

  for (; *format != '\0';) {
    if (*format++ == '%') {
      /* A directive. */
      unsigned int width = 0;
      unsigned int precision = 0;
      unsigned int length;
      /* Parse flags. */
      for (;;) {
        if (*format == ' ' || *format == '+' || *format == '-'
            || *format == '#' || *format == '0' || *format == '\'')
          format++;
        else
          break;
      }
      /* Parse width. */
      if (*format == '*')
        error(EXIT_FAILURE,0,
              /* TRANSLATORS: An error message.
                 The %s placeholder expands to a command-line option.  */
              _("%s argument: A format directive with a variable width is not allowed here."),
              param_name);
      if (isdigit (*format)) {
        do {
          width = 10*width + (*format - '0');
          format++;
        } while (isdigit (*format));
      }
      /* Parse precision. */
      if (*format == '.') {
        format++;
        if (*format == '*')
          error(EXIT_FAILURE,0,
                /* TRANSLATORS: An error message.
                   The %s placeholder expands to a command-line option.  */
                _("%s argument: A format directive with a variable precision is not allowed here."),
                param_name);
        if (isdigit (*format)) {
          do {
            precision = 10*precision + (*format - '0');
            format++;
          } while (isdigit (*format));
        }
      }
      /* Parse size. */
      switch (*format) {
        case 'h': case 'l': case 'L': case 'q':
        case 'j': case 'z': case 'Z': case 't':
          error(EXIT_FAILURE,0,
                /* TRANSLATORS: An error message.
                   The %s placeholder expands to a command-line option.  */
                _("%s argument: A format directive with a size is not allowed here."),
                param_name);
      }
      /* Parse end of directive. */
      switch (*format) {
        case '%':
          length = 1;
          break;
        case 'u': case 'o': case 'x': case 'X':
          if (*format == 'u') {
            length = (unsigned int) (sizeof (unsigned int) * CHAR_BIT
                                     * 0.30103 /* binary -> decimal */
                                    )
                     + 1; /* turn floor into ceil */
            if (length < precision)
              length = precision;
            length *= 2; /* estimate for FLAG_GROUP */
            length += 1; /* account for leading sign */
          } else if (*format == 'o') {
            length = (unsigned int) (sizeof (unsigned int) * CHAR_BIT
                                     * 0.333334 /* binary -> octal */
                                    )
                     + 1; /* turn floor into ceil */
            if (length < precision)
              length = precision;
            length += 1; /* account for leading sign */
          } else { /* 'x', 'X' */
            length = (unsigned int) (sizeof (unsigned int) * CHAR_BIT
                                     * 0.25 /* binary -> hexadecimal */
                                    )
                     + 1; /* turn floor into ceil */
            if (length < precision)
              length = precision;
            length += 2; /* account for leading sign or alternate form */
          }
          unnumbered_arg_count++;
          break;
        default:
          if (*format == '\0')
            error(EXIT_FAILURE,0,
                  /* TRANSLATORS: An error message.
                     The %s placeholder expands to a command-line option.  */
                  _("%s argument: The string ends in the middle of a directive."),
                  param_name);
          else if (c_isprint(*format))
            error(EXIT_FAILURE,0,
                  /* TRANSLATORS: An error message.
                     The %s placeholder expands to a command-line option.
                     The %c placeholder expands to an unknown format directive.  */
                  _("%s argument: The character '%c' is not a valid conversion specifier."),
                  param_name,*format);
          else
            error(EXIT_FAILURE,0,
                  /* TRANSLATORS: An error message.
                     The %s placeholder expands to a command-line option.  */
                  _("%s argument: The character that terminates the format directive is not a valid conversion specifier."),
                  param_name);
          abort(); /*NOTREACHED*/
      }
      format++;
      if (length < width)
        length = width;
      maxsize += length;
    } else
      maxsize++;
  }
  if (unnumbered_arg_count > 1)
    error(EXIT_FAILURE,0,
          /* TRANSLATORS: An error message.
             The %s placeholder expands to a command-line option.
             The %u placeholder expands to the number of arguments consumed by the format string.  */
          ngettext("%s argument: The format string consumes more than one argument: %u argument.",
                   "%s argument: The format string consumes more than one argument: %u arguments.",
                   unnumbered_arg_count),
          param_name,unnumbered_arg_count);
  return maxsize;
}