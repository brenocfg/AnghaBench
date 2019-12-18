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
 char* TYPE_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  java_primitive_type (char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void
java_demangled_signature_copy (char *result, char *signature)
{
  int array = 0;
  char *ptr;
  int i;
  while (*signature == '[')
    {
      array++;
      signature++;
    }
  switch (signature[0])
    {
    case 'L':
      /* Subtract 2 for 'L' and ';', but add 1 for final nul. */
      signature++;
      ptr = result;
      for (; *signature != ';' && *signature != '\0'; signature++)
	{
	  if (*signature == '/')
	    *ptr++ = '.';
	  else
	    *ptr++ = *signature;
	}
      break;
    default:
      ptr = TYPE_NAME (java_primitive_type (signature[0]));
      i = strlen (ptr);
      strcpy (result, ptr);
      ptr = result + i;
      break;
    }
  while (--array >= 0)
    {
      *ptr++ = '[';
      *ptr++ = ']';
    }
}