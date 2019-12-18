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
struct ieee_info {int /*<<< orphan*/  abfd; int /*<<< orphan*/  const* bytes; } ;
typedef  int /*<<< orphan*/  bfd_byte ;

/* Variables and functions */
 char* bfd_get_filename (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
ieee_error (struct ieee_info *info, const bfd_byte *p, const char *s)
{
  if (p != NULL)
    fprintf (stderr, "%s: 0x%lx: %s (0x%x)\n", bfd_get_filename (info->abfd),
	     (unsigned long) (p - info->bytes), s, *p);
  else
    fprintf (stderr, "%s: %s\n", bfd_get_filename (info->abfd), s);
}