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
typedef  unsigned char unw_word ;

/* Variables and functions */
 int /*<<< orphan*/  R1 ; 
 int /*<<< orphan*/  UNW_DEC_PROLOGUE (int /*<<< orphan*/ ,int,unsigned char,void*) ; 

__attribute__((used)) static unsigned char *
unw_decode_r1 (unsigned char *dp, unsigned char code, void *arg)
{
  int body = (code & 0x20) != 0;
  unw_word rlen;

  rlen = (code & 0x1f);
  UNW_DEC_PROLOGUE(R1, body, rlen, arg);
  return dp;
}