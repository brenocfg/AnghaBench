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
typedef  int /*<<< orphan*/  outf_p ;

/* Variables and functions */
 scalar_t__ ISALNUM (char const) ; 
 char* get_output_file_name (char const*) ; 
 int /*<<< orphan*/  oprintf (int /*<<< orphan*/ ,char*,char const) ; 

__attribute__((used)) static void
put_mangled_filename (outf_p f, const char *fn)
{
  const char *name = get_output_file_name (fn);
  for (; *name != 0; name++)
    if (ISALNUM (*name))
      oprintf (f, "%c", *name);
    else
      oprintf (f, "%c", '_');
}