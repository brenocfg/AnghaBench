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
 int /*<<< orphan*/  UNW_DEC_RESTORE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,void*) ; 
 int /*<<< orphan*/  UNW_DEC_SPILL_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,unsigned char,unsigned char,void*) ; 
 int /*<<< orphan*/  X2 ; 
 int /*<<< orphan*/  unw_decode_uleb128 (unsigned char**) ; 

__attribute__((used)) static unsigned char *
unw_decode_x2 (unsigned char *dp, unsigned char code, void *arg)
{
  unsigned char byte1, byte2, abreg, x, ytreg;
  unw_word t;

  byte1 = *dp++; byte2 = *dp++;
  t = unw_decode_uleb128 (&dp);
  abreg = (byte1 & 0x7f);
  ytreg = byte2;
  x = (byte1 >> 7) & 1;
  if ((byte1 & 0x80) == 0 && ytreg == 0)
    UNW_DEC_RESTORE(X2, t, abreg, arg);
  else
    UNW_DEC_SPILL_REG(X2, t, abreg, x, ytreg, arg);
  return dp;
}