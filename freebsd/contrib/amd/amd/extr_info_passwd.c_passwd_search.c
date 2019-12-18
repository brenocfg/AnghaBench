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
typedef  int /*<<< orphan*/  val ;
typedef  int /*<<< orphan*/  time_t ;
struct passwd {char* pw_dir; } ;
typedef  int /*<<< orphan*/  rhost ;
typedef  int /*<<< orphan*/  mnt_map ;

/* Variables and functions */
 int ENOENT ; 
 int MAXHOSTNAMELEN ; 
 int MAXPATHLEN ; 
 scalar_t__ STREQ (char*,char*) ; 
 int /*<<< orphan*/  XFREE (char*) ; 
 int /*<<< orphan*/  dlog (char*,char*,char*,char*) ; 
 struct passwd* getpwnam (char*) ; 
 char* strchr (char*,char) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,char*,char*,char*,char*,char*) ; 
 char* xstrdup (char*) ; 
 int /*<<< orphan*/  xstrlcat (char*,char*,int) ; 

int
passwd_search(mnt_map *m, char *map, char *key, char **pval, time_t *tp)
{
  char *dir = NULL;
  struct passwd *pw;

  if (STREQ(key, "/defaults")) {
    *pval = xstrdup("type:=nfs");
    return 0;
  }
  pw = getpwnam(key);

  if (pw) {
    /*
     * We chop the home directory up as follows:
     * /anydir/dom1/dom2/dom3/user
     *
     * and return
     * rfs:=/anydir/dom3;rhost:=dom3.dom2.dom1;sublink:=user
     * and now have
     * var0:=pw-prefix:=anydir
     * var1:=pw-rhost:=dom3.dom2.dom1
     * var2:=pw-user:=user
     * var3:=pw-home:=/anydir/dom1/dom2/dom3/user
     *
     * This allows cross-domain entries in your passwd file.
     * ... but forget about security!
     */
    char *user;
    char *p, *q;
    char val[MAXPATHLEN];
    char rhost[MAXHOSTNAMELEN];
    dir = xstrdup(pw->pw_dir);

    /*
     * Find user name.  If no / then Invalid...
     */
    user = strrchr(dir, '/');
    if (!user)
      goto enoent;
    *user++ = '\0';

    /*
     * Find start of host "path".  If no / then Invalid...
     */
    p = strchr(dir + 1, '/');
    if (!p)
      goto enoent;
    *p++ = '\0';

    /*
     * At this point, p is dom1/dom2/dom3
     * Copy, backwards, into rhost replacing
     * / with .
     */
    rhost[0] = '\0';
    do {
      q = strrchr(p, '/');
      if (q) {
	xstrlcat(rhost, q + 1, sizeof(rhost));
	xstrlcat(rhost, ".", sizeof(rhost));
	*q = '\0';
      } else {
	xstrlcat(rhost, p, sizeof(rhost));
      }
    } while (q);

    /*
     * Sanity check
     */
    if (*rhost == '\0' || *user == '\0' || *dir == '\0')
      goto enoent;

    /*
     * Make up return string
     */
    q = strchr(rhost, '.');
    if (q)
      *q = '\0';
    p = strchr(map, ':');
    if (p)
      p++;
    else
      p = "type:=nfs;rfs:=/${var0}/${var1};rhost:=${var1};sublink:=${var2};fs:=${autodir}${var3}";
    xsnprintf(val, sizeof(val), "var0:=%s;var1:=%s;var2:=%s;var3:=%s;%s",
	      dir+1, rhost, user, pw->pw_dir, p);
    dlog("passwd_search: map=%s key=%s -> %s", map, key, val);
    if (q)
      *q = '.';
    *pval = xstrdup(val);
    return 0;
  }

enoent:
  XFREE(dir);

  return ENOENT;
}