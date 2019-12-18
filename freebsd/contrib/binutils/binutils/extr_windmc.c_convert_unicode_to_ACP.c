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
typedef  int /*<<< orphan*/  unichar ;
typedef  int /*<<< orphan*/  rc_uint_type ;

/* Variables and functions */
 int /*<<< orphan*/  codepage_from_unicode (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char**,scalar_t__) ; 
 int /*<<< orphan*/  fatal (char*,long) ; 
 scalar_t__ mcset_codepage_out ; 

__attribute__((used)) static char *
convert_unicode_to_ACP (const unichar *usz)
{
  char *s;
  rc_uint_type l;

  if (! usz)
    return NULL;
  codepage_from_unicode (&l, usz, &s, mcset_codepage_out);
  if (! s)
    fatal ("unicode string not mappable to ASCII codepage 0x%lx.\n", (long) mcset_codepage_out);
  return s;
}