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
typedef  int /*<<< orphan*/  common_header_type ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  parse_int (int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
parse_i (common_header_type *ieee, bfd_boolean *ok)
{
  bfd_vma x = 0;
  *ok = parse_int (ieee, &x);
  return x;
}