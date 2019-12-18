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
typedef  int /*<<< orphan*/  p ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fsi_log (char*,char*,char*,char*) ; 
 int /*<<< orphan*/  make_banner (int /*<<< orphan*/ *) ; 
 void stub1 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,char*,char*) ; 

FILE *
pref_open(char *pref, char *hn, void (*hdr) (FILE *, char *), char *arg)
{
  char p[MAXPATHLEN];
  FILE *ef;

  xsnprintf(p, sizeof(p), "%s%s", pref, hn);
  fsi_log("Writing %s info for %s to %s", pref, hn, p);
  ef = fopen(p, "w");
  if (ef) {
    (*hdr) (ef, arg);
    make_banner(ef);
  } else {
    error("can't open %s for writing", p);
  }

  return ef;
}