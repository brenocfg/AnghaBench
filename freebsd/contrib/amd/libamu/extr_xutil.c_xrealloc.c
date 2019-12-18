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
typedef  scalar_t__ voidp ;

/* Variables and functions */
 int /*<<< orphan*/  D_MEM ; 
 int /*<<< orphan*/  XLOG_DEBUG ; 
 int /*<<< orphan*/  XLOG_FATAL ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ amuDebug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  going_down (int) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ realloc (scalar_t__,unsigned int) ; 
 scalar_t__ xmalloc (unsigned int) ; 

voidp
xrealloc(voidp ptr, int len)
{
  if (amuDebug(D_MEM))
    plog(XLOG_DEBUG, "Reallocated size %d; block %p", len, ptr);

  if (len == 0)
    len = 1;

  if (ptr)
    ptr = (voidp) realloc(ptr, (unsigned) len);
  else
    ptr = (voidp) xmalloc((unsigned) len);

  if (!ptr) {
    plog(XLOG_FATAL, "Out of memory in realloc");
    going_down(1);
    abort();
  }
  return ptr;
}