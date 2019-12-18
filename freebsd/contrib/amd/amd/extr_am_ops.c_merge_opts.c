#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  oneopt ;
struct TYPE_3__ {char* mnt_opts; } ;
typedef  TYPE_1__ mntent_t ;

/* Variables and functions */
 int /*<<< orphan*/  XFREE (char*) ; 
 scalar_t__ amu_hasmntopt (TYPE_1__*,char*) ; 
 char* reverse_option (char*) ; 
 char* strchr (char*,char) ; 
 int strlen (char const*) ; 
 char* strtok (char*,char*) ; 
 char* xmalloc (size_t) ; 
 char* xstrdup (char const*) ; 
 int /*<<< orphan*/  xstrlcat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  xstrlcpy (char*,char const*,size_t) ; 

__attribute__((used)) static char *
merge_opts(const char *opts1, const char *opts2)
{
  mntent_t mnt2;		/* place holder for opts2 */
  char *newstr;			/* new string to return (malloc'ed) */
  char *tmpstr;			/* temp */
  char *eq;			/* pointer to whatever follows '=' within temp */
  char oneopt[80];		/* one option w/o value if any */
  char *revoneopt;		/* reverse of oneopt */
  size_t len = strlen(opts1) + strlen(opts2) + 2; /* space for "," and NULL */
  char *s1 = xstrdup(opts1);	/* copy of opts1 to munge */

  /* initialization */
  mnt2.mnt_opts = (char *) opts2;
  newstr = xmalloc(len);
  newstr[0] = '\0';

  for (tmpstr = strtok(s1, ",");
       tmpstr;
       tmpstr = strtok(NULL, ",")) {
    /* copy option to temp buffer */
    xstrlcpy(oneopt, tmpstr, sizeof(oneopt));
    /* if option has a value such as rsize=1024, chop the value part */
    if ((eq = strchr(oneopt, '=')))
      *eq = '\0';
    /* find reverse option of oneopt */
    revoneopt = reverse_option(oneopt);
    /* if option or its reverse exist in opts2, ignore it */
    if (amu_hasmntopt(&mnt2, oneopt) || amu_hasmntopt(&mnt2, revoneopt))
      continue;
    /* add option to returned string */
    if (newstr[0]) {
      xstrlcat(newstr, ",", len);
      xstrlcat(newstr, tmpstr, len);
    } else {
      xstrlcpy(newstr, tmpstr, len);
    }
  }

  /* finally, append opts2 itself */
  if (newstr[0]) {
    xstrlcat(newstr, ",", len);
    xstrlcat(newstr, opts2, len);
  } else {
    xstrlcpy(newstr, opts2, len);
  }

  XFREE(s1);
  return newstr;
}