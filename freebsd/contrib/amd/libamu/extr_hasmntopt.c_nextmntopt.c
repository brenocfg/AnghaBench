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
 scalar_t__ isspace (unsigned char) ; 

__attribute__((used)) static char *
nextmntopt(char **p)
{
  char *cp = *p;
  char *rp;

  /*
   * Skip past white space
   */
  while (*cp && isspace((unsigned char) *cp))
    cp++;

  /*
   * Word starts here
   */
  rp = cp;

  /*
   * Scan to send of string or separator
   */
  while (*cp && *cp != ',')
    cp++;

  /*
   * If separator found the overwrite with null char.
   */
  if (*cp) {
    *cp = '\0';
    cp++;
  }

  /*
   * Return value for next call
   */
  *p = cp;
  return rp;
}