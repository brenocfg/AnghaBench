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
typedef  scalar_t__ rc_uint_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  fatal (int /*<<< orphan*/ ,char const*,long,long) ; 
 scalar_t__ fread (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
get_data (FILE *e, bfd_byte *p, rc_uint_type c, const char *msg)
{
  rc_uint_type got; // $$$d

  got = (rc_uint_type) fread (p, 1, c, e);
  if (got == c)
    return;

  fatal (_("%s: read of %lu returned %lu"), msg, (long) c, (long) got);
}