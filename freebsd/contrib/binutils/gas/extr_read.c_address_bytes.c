#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* arch_info; } ;
struct TYPE_3__ {int bits_per_address; } ;

/* Variables and functions */
 TYPE_2__* stdoutput ; 

__attribute__((used)) static inline int
address_bytes (void)
{
  /* Choose smallest of 1, 2, 4, 8 bytes that is large enough to
     contain an address.  */
  int n = (stdoutput->arch_info->bits_per_address - 1) / 8;
  n |= n >> 1;
  n |= n >> 2;
  n += 1;
  return n;
}