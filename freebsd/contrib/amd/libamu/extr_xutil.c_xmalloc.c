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
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/  XLOG_FATAL ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ amuDebug (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  going_down (int) ; 
 scalar_t__ malloc (unsigned int) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sleep (int) ; 

voidp
xmalloc(int len)
{
  voidp p;
  int retries = 600;

  /*
   * Avoid malloc's which return NULL for malloc(0)
   */
  if (len == 0)
    len = 1;

  do {
    p = (voidp) malloc((unsigned) len);
    if (p) {
      if (amuDebug(D_MEM))
	plog(XLOG_DEBUG, "Allocated size %d; block %p", len, p);
      return p;
    }
    if (retries > 0) {
      plog(XLOG_ERROR, "Retrying memory allocation");
      sleep(1);
    }
  } while (--retries);

  plog(XLOG_FATAL, "Out of memory");
  going_down(1);

  abort();

  return 0;
}