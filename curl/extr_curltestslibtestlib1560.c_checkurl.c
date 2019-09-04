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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char const*) ; 

__attribute__((used)) static int checkurl(const char *url, const char *out)
{
  if(strcmp(out, url)) {
    fprintf(stderr, "Wanted: %s\nGot   : %s\n",
            out, url);
    return 1;
  }
  return 0;
}