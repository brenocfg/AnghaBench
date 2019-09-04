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
 int DMGL_PARAMS ; 
 int DMGL_TYPES ; 
 char* d_demangle (char const*,int,size_t*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 

char *
__cxa_demangle (const char *mangled_name, char *output_buffer,
                size_t *length, int *status)
{
  char *demangled;
  size_t alc;

  if (mangled_name == NULL)
    {
      if (status != NULL)
	*status = -3;
      return NULL;
    }

  if (output_buffer != NULL && length == NULL)
    {
      if (status != NULL)
	*status = -3;
      return NULL;
    }

  demangled = d_demangle (mangled_name, DMGL_PARAMS | DMGL_TYPES, &alc);

  if (demangled == NULL)
    {
      if (status != NULL)
	{
	  if (alc == 1)
	    *status = -1;
	  else
	    *status = -2;
	}
      return NULL;
    }

  if (output_buffer == NULL)
    {
      if (length != NULL)
	*length = alc;
    }
  else
    {
      if (strlen (demangled) < *length)
	{
	  strcpy (output_buffer, demangled);
	  free (demangled);
	  demangled = output_buffer;
	}
      else
	{
	  free (output_buffer);
	  *length = alc;
	}
    }

  if (status != NULL)
    *status = 0;

  return demangled;
}