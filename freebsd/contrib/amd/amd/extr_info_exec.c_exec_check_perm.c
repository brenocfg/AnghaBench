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
typedef  int /*<<< orphan*/  u_int ;
struct stat {int st_mode; scalar_t__ st_uid; } ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int S_ISGID ; 
 int /*<<< orphan*/  S_ISREG (int) ; 
 int S_ISUID ; 
 int S_IWOTH ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  dlog (char*) ; 
 int errno ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,char*,...) ; 
 scalar_t__ stat (char*,struct stat*) ; 

__attribute__((used)) static int
exec_check_perm(char *map)
{
  struct stat sb;

  /* sanity and permission checks */
  if (!map) {
    dlog("exec_check_permission got a NULL map");
    return EINVAL;
  }
  if (stat(map, &sb)) {
    plog(XLOG_ERROR, "map \"%s\" stat failure: %m", map);
    return errno;
  }
  if (!S_ISREG(sb.st_mode)) {
    plog(XLOG_ERROR, "map \"%s\" should be regular file", map);
    return EINVAL;
  }
  if (sb.st_uid != 0) {
    plog(XLOG_ERROR, "map \"%s\" owned by uid %u (must be 0)", map, (u_int) sb.st_uid);
    return EACCES;
  }
  if (!(sb.st_mode & S_IXUSR)) {
    plog(XLOG_ERROR, "map \"%s\" should be executable", map);
    return EACCES;
  }
  if (sb.st_mode & (S_ISUID|S_ISGID)) {
    plog(XLOG_ERROR, "map \"%s\" should not be setuid/setgid", map);
    return EACCES;
  }
  if (sb.st_mode & S_IWOTH) {
    plog(XLOG_ERROR, "map \"%s\" should not be world writeable", map);
    return EACCES;
  }

  return 0;			/* all is well */
}