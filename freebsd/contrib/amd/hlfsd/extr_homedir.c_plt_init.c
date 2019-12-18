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
typedef  int /*<<< orphan*/  username2uid_t ;
typedef  int /*<<< orphan*/  uid2home_t ;
struct passwd {char* pw_dir; int /*<<< orphan*/  pw_name; int /*<<< orphan*/  pw_uid; } ;

/* Variables and functions */
 scalar_t__ STREQ (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFREE (char*) ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  cur_pwtab_num ; 
 int /*<<< orphan*/  hlfsd_endpwent () ; 
 struct passwd* hlfsd_getpwent () ; 
 int /*<<< orphan*/  hlfsd_setpwent () ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  plt_compare_fxn ; 
 scalar_t__ plt_reset () ; 
 scalar_t__ pwtab ; 
 int /*<<< orphan*/  qsort (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 char* root_home ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  table_add (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unt_compare_fxn ; 
 scalar_t__ untab ; 
 char* xstrdup (char*) ; 

void
plt_init(void)
{
  struct passwd *pent_p;

  if (plt_reset() < 0)		/* could not reset table. skip. */
    return;

  plog(XLOG_INFO, "reading password map");

  hlfsd_setpwent();			/* prepare to read passwd entries */
  while ((pent_p = hlfsd_getpwent()) != (struct passwd *) NULL) {
    table_add(pent_p->pw_uid, pent_p->pw_dir, pent_p->pw_name);
    if (STREQ("root", pent_p->pw_name)) {
      int len;
      if (root_home)
	XFREE(root_home);
      root_home = xstrdup(pent_p->pw_dir);
      len = strlen(root_home);
      /* remove any trailing '/' chars from root's home (even if just one) */
      while (len > 0 && root_home[len - 1] == '/') {
	len--;
	root_home[len] = '\0';
      }
    }
  }
  hlfsd_endpwent();

  qsort((char *) pwtab, cur_pwtab_num, sizeof(uid2home_t),
	plt_compare_fxn);
  qsort((char *) untab, cur_pwtab_num, sizeof(username2uid_t),
	unt_compare_fxn);

  if (!root_home)
    root_home = xstrdup("");

  plog(XLOG_INFO, "password map read and sorted");
}