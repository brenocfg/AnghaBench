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
 int fchown (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ geteuid () ; 

__attribute__((used)) static int posixFchown(int fd, uid_t uid, gid_t gid){
  return geteuid() ? 0 : fchown(fd,uid,gid);
}