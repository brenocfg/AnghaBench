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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  gid_t ;

/* Variables and functions */

__attribute__((used)) static int robustFchown(int fd, uid_t uid, gid_t gid){
#if defined(HAVE_FCHOWN)
  return osGeteuid() ? 0 : osFchown(fd,uid,gid);
#else
  return 0;
#endif
}