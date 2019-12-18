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
 int /*<<< orphan*/ * fopen (char const*,char const*) ; 
 int /*<<< orphan*/  unlock_1 (int /*<<< orphan*/ * const) ; 

FILE *
fopen_unlocked (const char *path, const char *mode)		
{
  FILE *const fp = fopen (path, mode);
  unlock_1 (fp);
  return fp;
}