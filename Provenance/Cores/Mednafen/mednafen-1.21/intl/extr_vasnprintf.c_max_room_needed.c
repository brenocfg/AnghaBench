#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct TYPE_7__ {TYPE_2__* arg; } ;
typedef  TYPE_3__ arguments ;
typedef  int /*<<< orphan*/  arg_type ;
struct TYPE_5__ {char* a_string; int /*<<< orphan*/ * a_wide_string; } ;
struct TYPE_6__ {TYPE_1__ a; } ;
typedef  int FCHAR_T ;

/* Variables and functions */
 int CHAR_BIT ; 
 double DBL_DIG ; 
 double DBL_MAX_EXP ; 
 double LDBL_DIG ; 
 double LDBL_MAX_EXP ; 
 size_t MB_CUR_MAX ; 
 int /*<<< orphan*/  TYPE_LONGDOUBLE ; 
 int /*<<< orphan*/  TYPE_LONGINT ; 
 int /*<<< orphan*/  TYPE_LONGLONGINT ; 
 int /*<<< orphan*/  TYPE_ULONGINT ; 
 int /*<<< orphan*/  TYPE_ULONGLONGINT ; 
 int /*<<< orphan*/  TYPE_WIDE_CHAR ; 
 int /*<<< orphan*/  TYPE_WIDE_STRING ; 
 int /*<<< orphan*/  abort () ; 
 size_t local_strnlen (char const*,size_t) ; 
 size_t local_wcslen (int /*<<< orphan*/  const*) ; 
 size_t local_wcsnlen (int /*<<< orphan*/  const*,size_t) ; 
 size_t strlen (char const*) ; 
 size_t xsum (size_t,int) ; 

__attribute__((used)) static inline size_t
MAX_ROOM_NEEDED (const arguments *ap, size_t arg_index, FCHAR_T conversion,
                 arg_type type, int flags, size_t width, int has_precision,
                 size_t precision, int pad_ourselves)
{
  size_t tmp_length;

  switch (conversion)
    {
    case 'd': case 'i': case 'u':
# if HAVE_LONG_LONG_INT
      if (type == TYPE_LONGLONGINT || type == TYPE_ULONGLONGINT)
        tmp_length =
          (unsigned int) (sizeof (unsigned long long) * CHAR_BIT
                          * 0.30103 /* binary -> decimal */
                         )
          + 1; /* turn floor into ceil */
      else
# endif
      if (type == TYPE_LONGINT || type == TYPE_ULONGINT)
        tmp_length =
          (unsigned int) (sizeof (unsigned long) * CHAR_BIT
                          * 0.30103 /* binary -> decimal */
                         )
          + 1; /* turn floor into ceil */
      else
        tmp_length =
          (unsigned int) (sizeof (unsigned int) * CHAR_BIT
                          * 0.30103 /* binary -> decimal */
                         )
          + 1; /* turn floor into ceil */
      if (tmp_length < precision)
        tmp_length = precision;
      /* Multiply by 2, as an estimate for FLAG_GROUP.  */
      tmp_length = xsum (tmp_length, tmp_length);
      /* Add 1, to account for a leading sign.  */
      tmp_length = xsum (tmp_length, 1);
      break;

    case 'o':
# if HAVE_LONG_LONG_INT
      if (type == TYPE_LONGLONGINT || type == TYPE_ULONGLONGINT)
        tmp_length =
          (unsigned int) (sizeof (unsigned long long) * CHAR_BIT
                          * 0.333334 /* binary -> octal */
                         )
          + 1; /* turn floor into ceil */
      else
# endif
      if (type == TYPE_LONGINT || type == TYPE_ULONGINT)
        tmp_length =
          (unsigned int) (sizeof (unsigned long) * CHAR_BIT
                          * 0.333334 /* binary -> octal */
                         )
          + 1; /* turn floor into ceil */
      else
        tmp_length =
          (unsigned int) (sizeof (unsigned int) * CHAR_BIT
                          * 0.333334 /* binary -> octal */
                         )
          + 1; /* turn floor into ceil */
      if (tmp_length < precision)
        tmp_length = precision;
      /* Add 1, to account for a leading sign.  */
      tmp_length = xsum (tmp_length, 1);
      break;

    case 'x': case 'X':
# if HAVE_LONG_LONG_INT
      if (type == TYPE_LONGLONGINT || type == TYPE_ULONGLONGINT)
        tmp_length =
          (unsigned int) (sizeof (unsigned long long) * CHAR_BIT
                          * 0.25 /* binary -> hexadecimal */
                         )
          + 1; /* turn floor into ceil */
      else
# endif
      if (type == TYPE_LONGINT || type == TYPE_ULONGINT)
        tmp_length =
          (unsigned int) (sizeof (unsigned long) * CHAR_BIT
                          * 0.25 /* binary -> hexadecimal */
                         )
          + 1; /* turn floor into ceil */
      else
        tmp_length =
          (unsigned int) (sizeof (unsigned int) * CHAR_BIT
                          * 0.25 /* binary -> hexadecimal */
                         )
          + 1; /* turn floor into ceil */
      if (tmp_length < precision)
        tmp_length = precision;
      /* Add 2, to account for a leading sign or alternate form.  */
      tmp_length = xsum (tmp_length, 2);
      break;

    case 'f': case 'F':
      if (type == TYPE_LONGDOUBLE)
        tmp_length =
          (unsigned int) (LDBL_MAX_EXP
                          * 0.30103 /* binary -> decimal */
                          * 2 /* estimate for FLAG_GROUP */
                         )
          + 1 /* turn floor into ceil */
          + 10; /* sign, decimal point etc. */
      else
        tmp_length =
          (unsigned int) (DBL_MAX_EXP
                          * 0.30103 /* binary -> decimal */
                          * 2 /* estimate for FLAG_GROUP */
                         )
          + 1 /* turn floor into ceil */
          + 10; /* sign, decimal point etc. */
      tmp_length = xsum (tmp_length, precision);
      break;

    case 'e': case 'E': case 'g': case 'G':
      tmp_length =
        12; /* sign, decimal point, exponent etc. */
      tmp_length = xsum (tmp_length, precision);
      break;

    case 'a': case 'A':
      if (type == TYPE_LONGDOUBLE)
        tmp_length =
          (unsigned int) (LDBL_DIG
                          * 0.831 /* decimal -> hexadecimal */
                         )
          + 1; /* turn floor into ceil */
      else
        tmp_length =
          (unsigned int) (DBL_DIG
                          * 0.831 /* decimal -> hexadecimal */
                         )
          + 1; /* turn floor into ceil */
      if (tmp_length < precision)
        tmp_length = precision;
      /* Account for sign, decimal point etc. */
      tmp_length = xsum (tmp_length, 12);
      break;

    case 'c':
# if HAVE_WINT_T && !WIDE_CHAR_VERSION
      if (type == TYPE_WIDE_CHAR)
        tmp_length = MB_CUR_MAX;
      else
# endif
        tmp_length = 1;
      break;

    case 's':
# if HAVE_WCHAR_T
      if (type == TYPE_WIDE_STRING)
        {
#  if WIDE_CHAR_VERSION
          /* ISO C says about %ls in fwprintf:
               "If the precision is not specified or is greater than the size
                of the array, the array shall contain a null wide character."
             So if there is a precision, we must not use wcslen.  */
          const wchar_t *arg = ap->arg[arg_index].a.a_wide_string;

          if (has_precision)
            tmp_length = local_wcsnlen (arg, precision);
          else
            tmp_length = local_wcslen (arg);
#  else
          /* ISO C says about %ls in fprintf:
               "If a precision is specified, no more than that many bytes are
                written (including shift sequences, if any), and the array
                shall contain a null wide character if, to equal the multibyte
                character sequence length given by the precision, the function
                would need to access a wide character one past the end of the
                array."
             So if there is a precision, we must not use wcslen.  */
          /* This case has already been handled separately in VASNPRINTF.  */
          abort ();
#  endif
        }
      else
# endif
        {
# if WIDE_CHAR_VERSION
          /* ISO C says about %s in fwprintf:
               "If the precision is not specified or is greater than the size
                of the converted array, the converted array shall contain a
                null wide character."
             So if there is a precision, we must not use strlen.  */
          /* This case has already been handled separately in VASNPRINTF.  */
          abort ();
# else
          /* ISO C says about %s in fprintf:
               "If the precision is not specified or greater than the size of
                the array, the array shall contain a null character."
             So if there is a precision, we must not use strlen.  */
          const char *arg = ap->arg[arg_index].a.a_string;

          if (has_precision)
            tmp_length = local_strnlen (arg, precision);
          else
            tmp_length = strlen (arg);
# endif
        }
      break;

    case 'p':
      tmp_length =
        (unsigned int) (sizeof (void *) * CHAR_BIT
                        * 0.25 /* binary -> hexadecimal */
                       )
          + 1 /* turn floor into ceil */
          + 2; /* account for leading 0x */
      break;

    default:
      abort ();
    }

  if (!pad_ourselves)
    {
# if ENABLE_UNISTDIO
      /* Padding considers the number of characters, therefore the number of
         elements after padding may be
           > max (tmp_length, width)
         but is certainly
           <= tmp_length + width.  */
      tmp_length = xsum (tmp_length, width);
# else
      /* Padding considers the number of elements, says POSIX.  */
      if (tmp_length < width)
        tmp_length = width;
# endif
    }

  tmp_length = xsum (tmp_length, 1); /* account for trailing NUL */

  return tmp_length;
}