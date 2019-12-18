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
 int /*<<< orphan*/  IS_DIR_SEPARATOR (char) ; 
 char* PREFIX ; 
 scalar_t__ alloca (int) ; 
 char* concat (char const*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_key_value (char*) ; 
 char* getenv (char*) ; 
 char* std_prefix ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static char *
translate_name (char *name)
{
  char code;
  char *key, *old_name;
  const char *prefix;
  int keylen;

  for (;;)
    {
      code = name[0];
      if (code != '@' && code != '$')
	break;

      for (keylen = 0;
	   (name[keylen + 1] != 0 && !IS_DIR_SEPARATOR (name[keylen + 1]));
	   keylen++)
	;

      key = (char *) alloca (keylen + 1);
      strncpy (key, &name[1], keylen);
      key[keylen] = 0;

      if (code == '@')
	{
	  prefix = get_key_value (key);
	  if (prefix == 0)
	    prefix = std_prefix;
	}
      else
	prefix = getenv (key);

      if (prefix == 0)
	prefix = PREFIX;

      /* We used to strip trailing DIR_SEPARATORs here, but that can
	 sometimes yield a result with no separator when one was coded
	 and intended by the user, causing two path components to run
	 together.  */

      old_name = name;
      name = concat (prefix, &name[keylen + 1], NULL);
      free (old_name);
    }

  return name;
}