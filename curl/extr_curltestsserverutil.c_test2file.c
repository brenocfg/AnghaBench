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
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_DATA_PATH ; 
 int /*<<< orphan*/  msnprintf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  path ; 

char *test2file(long testno)
{
  static char filename[256];
  msnprintf(filename, sizeof(filename), TEST_DATA_PATH, path, testno);
  return filename;
}