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
typedef  int /*<<< orphan*/  am_node ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static am_node *
foofs_lookuppn(am_node *mp, char *fname, int *error_return, int op)
{
  int error = 0;

  plog(XLOG_INFO, "entering foofs_lookuppn...");

  error = EPERM;			/* XXX: fixme */

  *error_return = error;
  return NULL;
}