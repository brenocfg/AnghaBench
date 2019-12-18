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
typedef  int /*<<< orphan*/  unw_word ;

/* Variables and functions */
 int /*<<< orphan*/  R2 ; 
 int /*<<< orphan*/  UNW_DEC_PROLOGUE_GR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,unsigned char,void*) ; 
 int /*<<< orphan*/  unw_decode_uleb128 (unsigned char**) ; 

__attribute__((used)) static unsigned char *
unw_decode_r2 (unsigned char *dp, unsigned char code, void *arg)
{
  unsigned char byte1, mask, grsave;
  unw_word rlen;

  byte1 = *dp++;

  mask = ((code & 0x7) << 1) | ((byte1 >> 7) & 1);
  grsave = (byte1 & 0x7f);
  rlen = unw_decode_uleb128 (&dp);
  UNW_DEC_PROLOGUE_GR(R2, rlen, mask, grsave, arg);
  return dp;
}