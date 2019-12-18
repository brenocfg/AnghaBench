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
 int /*<<< orphan*/ * fopen64 (char const*,char const*) ; 

FILE *
real_fopen (const char *filename, const char *modes)
{
#if defined (HAVE_FOPEN64)
  return fopen64 (filename, modes);
#else
  return fopen (filename, modes);
#endif
}