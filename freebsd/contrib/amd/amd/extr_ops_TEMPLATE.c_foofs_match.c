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
typedef  int /*<<< orphan*/  am_opts ;

/* Variables and functions */
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static char *
foofs_match(am_opts *fo)
{
  char *cp = "fill this with a way to find the match";

  plog(XLOG_INFO, "entering foofs_match...");

  if (cp)
    return cp;			/* OK */

  return NULL;			/* not OK */
}