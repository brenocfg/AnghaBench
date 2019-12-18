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
 int /*<<< orphan*/  P1 ; 
 int /*<<< orphan*/  UNW_DEC_BR_MEM (int /*<<< orphan*/ ,unsigned char,void*) ; 

__attribute__((used)) static unsigned char *
unw_decode_p1 (unsigned char *dp, unsigned char code, void *arg)
{
  unsigned char brmask = (code & 0x1f);

  UNW_DEC_BR_MEM(P1, brmask, arg);
  return dp;
}