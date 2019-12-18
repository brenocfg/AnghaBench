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
 int /*<<< orphan*/  SUN_KEY_SUB ; 
 int /*<<< orphan*/  XFREE (char*) ; 
 char* sun_expand2amd (char*) ; 
 char* sun_strsub (char const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xstrlcat (char*,char*,size_t) ; 

__attribute__((used)) static void
sun_append_str(char *dest,
	       size_t destlen,
	       const char *key,
	       const char *str)
{
  char *sub = NULL, *sub2 = NULL, *out = NULL;

  /* By default we are going to just write the original string. */
  out = (char*)str;

  /*
   * Resolve variable substitutions in two steps; 1) replace any key
   * map substitutions with the entry key 2) expand any variable
   * substitutions i.e $HOST.
   *
   * Try to replace the key substitution '&'. If this function returns
   * with a new string, one or more key subs. where replaced with the
   * entry key.
   */
  if ((sub = sun_strsub(str, SUN_KEY_SUB, "${key}")) != NULL) {
    out = sub;
    /*
     * Try to convert any variable substitutions. If this function
     * returns a new string one or more var subs where expanded.
     */
    if ((sub2 = sun_expand2amd(sub)) != NULL) {
      out = sub2;
    }
  }
  /*
   * Try to convert any variable substitutions. If this function
   * returns a new string one or more var subs where expanded.
   */
  else if (out != NULL && (sub = sun_expand2amd(out)) != NULL) {
    out = sub;
  }

  if (out != NULL) {
    xstrlcat(dest, out, destlen);
  }
  XFREE(sub);
  XFREE(sub2);
}