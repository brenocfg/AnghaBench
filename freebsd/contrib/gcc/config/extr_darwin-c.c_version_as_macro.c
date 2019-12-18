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
 int /*<<< orphan*/  ISDIGIT (char) ; 
 char* darwin_macosx_version_min ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

__attribute__((used)) static const char *
version_as_macro (void)
{
  static char result[] = "1000";

  if (strncmp (darwin_macosx_version_min, "10.", 3) != 0)
    goto fail;
  if (! ISDIGIT (darwin_macosx_version_min[3]))
    goto fail;
  result[2] = darwin_macosx_version_min[3];
  if (darwin_macosx_version_min[4] != '\0')
    {
      if (darwin_macosx_version_min[4] != '.')
	goto fail;
      if (! ISDIGIT (darwin_macosx_version_min[5]))
	goto fail;
      if (darwin_macosx_version_min[6] != '\0')
	goto fail;
      result[3] = darwin_macosx_version_min[5];
    }
  else
    result[3] = '0';

  return result;

 fail:
  error ("Unknown value %qs of -mmacosx-version-min",
	 darwin_macosx_version_min);
  return "1000";
}