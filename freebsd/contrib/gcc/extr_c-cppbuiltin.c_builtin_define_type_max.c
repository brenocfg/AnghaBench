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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 scalar_t__ alloca (scalar_t__) ; 
 int /*<<< orphan*/  cpp_define (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  parse_in ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*,char const*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static void
builtin_define_type_max (const char *macro, tree type, int is_long)
{
  static const char *const values[]
    = { "127", "255",
	"32767", "65535",
	"2147483647", "4294967295",
	"9223372036854775807", "18446744073709551615",
	"170141183460469231731687303715884105727",
	"340282366920938463463374607431768211455" };
  static const char *const suffixes[] = { "", "U", "L", "UL", "LL", "ULL" };

  const char *value, *suffix;
  char *buf;
  size_t idx;

  /* Pre-rendering the values mean we don't have to futz with printing a
     multi-word decimal value.  There are also a very limited number of
     precisions that we support, so it's really a waste of time.  */
  switch (TYPE_PRECISION (type))
    {
    case 8:	idx = 0; break;
    case 16:	idx = 2; break;
    case 32:	idx = 4; break;
    case 64:	idx = 6; break;
    case 128:	idx = 8; break;
    default:    gcc_unreachable ();
    }

  value = values[idx + TYPE_UNSIGNED (type)];
  suffix = suffixes[is_long * 2 + TYPE_UNSIGNED (type)];

  buf = (char *) alloca (strlen (macro) + 1 + strlen (value)
                         + strlen (suffix) + 1);
  sprintf (buf, "%s=%s%s", macro, value, suffix);

  cpp_define (parse_in, buf);
}