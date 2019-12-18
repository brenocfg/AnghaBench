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
typedef  int /*<<< orphan*/  path ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  domain_strip (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsi_log (char*,char*,char*) ; 
 int /*<<< orphan*/  hostname ; 
 char* strrchr (char*,char) ; 
 char* xmalloc (int) ; 
 int /*<<< orphan*/  xstrlcat (char*,char*,int) ; 
 int /*<<< orphan*/  xstrlcpy (char*,char*,int) ; 

__attribute__((used)) static char *
compute_hostpath(char *hn)
{
  char *p = xmalloc(MAXPATHLEN);
  char *d;
  char path[MAXPATHLEN];

  xstrlcpy(p, hn, MAXPATHLEN);
  domain_strip(p, hostname);
  path[0] = '\0';

  do {
    d = strrchr(p, '.');
    if (d) {
      *d = '\0';
      xstrlcat(path, d + 1, sizeof(path));
      xstrlcat(path, "/", sizeof(path));
    } else {
      xstrlcat(path, p, sizeof(path));
    }
  } while (d);

  fsi_log("hostpath of '%s' is '%s'", hn, path);

  xstrlcpy(p, path, MAXPATHLEN);
  return p;
}