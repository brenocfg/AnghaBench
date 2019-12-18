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
 scalar_t__ isalnum (unsigned char) ; 
 scalar_t__ isalpha (unsigned char) ; 
 scalar_t__ isdigit (unsigned char) ; 
 scalar_t__ malloc (int) ; 
 char* stpcpy (char*,char*) ; 
 int /*<<< orphan*/  tolower (unsigned char) ; 

const char *
_nl_normalize_codeset (const char *codeset, size_t name_len)
{
  size_t len = 0;
  int only_digit = 1;
  char *retval;
  char *wp;
  size_t cnt;

  for (cnt = 0; cnt < name_len; ++cnt)
    if (isalnum ((unsigned char) codeset[cnt]))
      {
	++len;

	if (isalpha ((unsigned char) codeset[cnt]))
	  only_digit = 0;
      }

  retval = (char *) malloc ((only_digit ? 3 : 0) + len + 1);

  if (retval != NULL)
    {
      if (only_digit)
	wp = stpcpy (retval, "iso");
      else
	wp = retval;

      for (cnt = 0; cnt < name_len; ++cnt)
	if (isalpha ((unsigned char) codeset[cnt]))
	  *wp++ = tolower ((unsigned char) codeset[cnt]);
	else if (isdigit ((unsigned char) codeset[cnt]))
	  *wp++ = codeset[cnt];

      *wp = '\0';
    }

  return (const char *) retval;
}