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

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  f_in ; 
 int /*<<< orphan*/  file_name ; 
 int fread (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
input_file_get (char *buf, int buflen)
{
  int size;

  size = fread (buf, sizeof (char), buflen, f_in);
  if (size < 0)
    {
      as_bad (_("can't read from %s: %s"), file_name, xstrerror (errno));
      size = 0;
    }
  return size;
}