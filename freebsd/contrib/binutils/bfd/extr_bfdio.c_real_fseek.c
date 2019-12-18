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
typedef  int /*<<< orphan*/  file_ptr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int fseeko (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int fseeko64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int
real_fseek (FILE *file, file_ptr offset, int whence)
{
#if defined (HAVE_FSEEKO64)
  return fseeko64 (file, offset, whence);
#elif defined (HAVE_FSEEKO)
  return fseeko (file, offset, whence);
#else
  return fseek (file, offset, whence);
#endif
}