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
struct type {int dummy; } ;

/* Variables and functions */
 int TYPE_FIELD_BITPOS (struct type*,int) ; 

__attribute__((used)) static unsigned int
field_offset (struct type *type, int f)
{
  int n = TYPE_FIELD_BITPOS (type, f);
  /* Kludge (temporary?) to fix problem with dwarf output. */
  if (n < 0)
    return (unsigned int) n & 0xffff;
  else
    return n;
}