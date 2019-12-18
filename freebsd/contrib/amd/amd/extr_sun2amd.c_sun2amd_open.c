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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  XLOG_ERROR ; 
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static FILE *
sun2amd_open(const char *path, const char *mode)
{
  FILE *retval = NULL;

  if ((retval = fopen(path,mode)) == NULL) {
    plog(XLOG_ERROR,"could not open file %s",path);
  }

  return retval;
}