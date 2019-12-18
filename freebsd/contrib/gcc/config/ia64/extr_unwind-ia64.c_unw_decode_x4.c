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
 int /*<<< orphan*/  UNW_DEC_RESTORE_P (int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ,unsigned char,void*) ; 
 int /*<<< orphan*/  UNW_DEC_SPILL_REG_P (int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ,unsigned char,unsigned char,unsigned char,void*) ; 
 int /*<<< orphan*/  X4 ; 
 int /*<<< orphan*/  unw_decode_uleb128 (unsigned char**) ; 

__attribute__((used)) static unsigned char *
unw_decode_x4 (unsigned char *dp,
	       unsigned char code __attribute__((unused)),
	       void *arg)
{
  unsigned char byte1, byte2, byte3, qp, abreg, x, ytreg;
  unw_word t;

  byte1 = *dp++; byte2 = *dp++; byte3 = *dp++;
  t = unw_decode_uleb128 (&dp);

  qp = (byte1 & 0x3f);
  abreg = (byte2 & 0x7f);
  x = (byte2 >> 7) & 1;
  ytreg = byte3;

  if ((byte2 & 0x80) == 0 && byte3 == 0)
    UNW_DEC_RESTORE_P(X4, qp, t, abreg, arg);
  else
    UNW_DEC_SPILL_REG_P(X4, qp, t, abreg, x, ytreg, arg);
  return dp;
}