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
typedef  int /*<<< orphan*/  dict_ent ;

/* Variables and functions */
 int /*<<< orphan*/  XFREE (char*) ; 
 int /*<<< orphan*/ * dict_locate (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dict_of_volnames ; 
 int /*<<< orphan*/  fsi_log (char*,char*) ; 
 char* strrchr (char*,char) ; 
 char* xstrdup (char*) ; 

__attribute__((used)) static dict_ent *
find_volname(char *nn)
{
  dict_ent *de;
  char *p = xstrdup(nn);
  char *q;

  do {
    fsi_log("Searching for volname %s", p);
    de = dict_locate(dict_of_volnames, p);
    q = strrchr(p, '/');
    if (q)
      *q = '\0';
  } while (!de && q);

  XFREE(p);
  return de;
}