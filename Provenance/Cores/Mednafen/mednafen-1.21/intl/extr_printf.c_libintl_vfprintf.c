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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EOVERFLOW ; 
 size_t INT_MAX ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t fwrite (char*,int,size_t,int /*<<< orphan*/ *) ; 
 char* libintl_vasnprintf (int /*<<< orphan*/ *,size_t*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 int vfprintf (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

int
libintl_vfprintf (FILE *stream, const char *format, va_list args)
{
  if (strchr (format, '$') == NULL)
    return vfprintf (stream, format, args);
  else
    {
      size_t length;
      char *result = libintl_vasnprintf (NULL, &length, format, args);
      int retval = -1;
      if (result != NULL)
        {
          size_t written = fwrite (result, 1, length, stream);
          free (result);
          if (written == length)
            {
              if (length > INT_MAX)
                errno = EOVERFLOW;
              else
                retval = length;
            }
        }
      return retval;
    }
}