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
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static inline int find_and_clear_bit_16(unsigned long *field)
{
  int rv;

  if (*field == 0)
    panic("No free mscp");

  asm volatile (
	"xorl %0,%0\n\t"
	"0: bsfw %1,%w0\n\t"
	"btr %0,%1\n\t"
	"jnc 0b"
	: "=&r" (rv), "=m" (*field) :);

  return rv;
}