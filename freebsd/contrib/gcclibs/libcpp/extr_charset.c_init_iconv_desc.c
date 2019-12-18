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
struct cset_converter {scalar_t__ cd; void* func; } ;
typedef  scalar_t__ iconv_t ;
typedef  int /*<<< orphan*/  cpp_reader ;
struct TYPE_3__ {char const* pair; scalar_t__ fake_cd; void* func; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CPP_DL_ERROR ; 
 scalar_t__ EINVAL ; 
 scalar_t__ HAVE_ICONV ; 
 scalar_t__ alloca (scalar_t__) ; 
 TYPE_1__* conversion_tab ; 
 void* convert_no_conversion ; 
 void* convert_using_iconv ; 
 int /*<<< orphan*/  cpp_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cpp_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 scalar_t__ errno ; 
 scalar_t__ iconv_open (char const*,char const*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,char const*) ; 
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static struct cset_converter
init_iconv_desc (cpp_reader *pfile, const char *to, const char *from)
{
  struct cset_converter ret;
  char *pair;
  size_t i;

  if (!strcasecmp (to, from))
    {
      ret.func = convert_no_conversion;
      ret.cd = (iconv_t) -1;
      return ret;
    }

  pair = (char *) alloca(strlen(to) + strlen(from) + 2);

  strcpy(pair, from);
  strcat(pair, "/");
  strcat(pair, to);
  for (i = 0; i < ARRAY_SIZE (conversion_tab); i++)
    if (!strcasecmp (pair, conversion_tab[i].pair))
      {
	ret.func = conversion_tab[i].func;
	ret.cd = conversion_tab[i].fake_cd;
	return ret;
      }

  /* No custom converter - try iconv.  */
  if (HAVE_ICONV)
    {
      ret.func = convert_using_iconv;
      ret.cd = iconv_open (to, from);

      if (ret.cd == (iconv_t) -1)
	{
	  if (errno == EINVAL)
	    cpp_error (pfile, CPP_DL_ERROR, /* FIXME should be DL_SORRY */
		       "conversion from %s to %s not supported by iconv",
		       from, to);
	  else
	    cpp_errno (pfile, CPP_DL_ERROR, "iconv_open");

	  ret.func = convert_no_conversion;
	}
    }
  else
    {
      cpp_error (pfile, CPP_DL_ERROR, /* FIXME: should be DL_SORRY */
		 "no iconv implementation, cannot convert from %s to %s",
		 from, to);
      ret.func = convert_no_conversion;
      ret.cd = (iconv_t) -1;
    }
  return ret;
}