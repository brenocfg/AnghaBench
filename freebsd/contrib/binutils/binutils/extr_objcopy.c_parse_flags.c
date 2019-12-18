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
typedef  int /*<<< orphan*/  flagword ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_FLAG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEC_ALLOC ; 
 int /*<<< orphan*/  SEC_CODE ; 
 int /*<<< orphan*/  SEC_COFF_SHARED ; 
 int /*<<< orphan*/  SEC_DATA ; 
 int /*<<< orphan*/  SEC_DEBUGGING ; 
 int /*<<< orphan*/  SEC_HAS_CONTENTS ; 
 int /*<<< orphan*/  SEC_LOAD ; 
 int /*<<< orphan*/  SEC_NEVER_LOAD ; 
 int /*<<< orphan*/  SEC_NO_FLAGS ; 
 int /*<<< orphan*/  SEC_READONLY ; 
 int /*<<< orphan*/  SEC_ROM ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  non_fatal (int /*<<< orphan*/ ,char*) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 char* xmalloc (int) ; 

__attribute__((used)) static flagword
parse_flags (const char *s)
{
  flagword ret;
  const char *snext;
  int len;

  ret = SEC_NO_FLAGS;

  do
    {
      snext = strchr (s, ',');
      if (snext == NULL)
	len = strlen (s);
      else
	{
	  len = snext - s;
	  ++snext;
	}

      if (0) ;
#define PARSE_FLAG(fname,fval) \
  else if (strncasecmp (fname, s, len) == 0) ret |= fval
      PARSE_FLAG ("alloc", SEC_ALLOC);
      PARSE_FLAG ("load", SEC_LOAD);
      PARSE_FLAG ("noload", SEC_NEVER_LOAD);
      PARSE_FLAG ("readonly", SEC_READONLY);
      PARSE_FLAG ("debug", SEC_DEBUGGING);
      PARSE_FLAG ("code", SEC_CODE);
      PARSE_FLAG ("data", SEC_DATA);
      PARSE_FLAG ("rom", SEC_ROM);
      PARSE_FLAG ("share", SEC_COFF_SHARED);
      PARSE_FLAG ("contents", SEC_HAS_CONTENTS);
#undef PARSE_FLAG
      else
	{
	  char *copy;

	  copy = xmalloc (len + 1);
	  strncpy (copy, s, len);
	  copy[len] = '\0';
	  non_fatal (_("unrecognized section flag `%s'"), copy);
	  fatal (_("supported flags: %s"),
		 "alloc, load, noload, readonly, debug, code, data, rom, share, contents");
	}

      s = snext;
    }
  while (s != NULL);

  return ret;
}