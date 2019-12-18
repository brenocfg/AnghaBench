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

__attribute__((used)) static int
foofs_mount(am_node *mp)
{
  int error = 0;

  plog(XLOG_INFO, "entering foofs_mount...");

  error = EPERM;		/* XXX: fixme */
  return error;
}