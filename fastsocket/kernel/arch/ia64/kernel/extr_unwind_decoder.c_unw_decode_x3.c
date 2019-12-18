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
 int /*<<< orphan*/  UNW_DEC_SPILL_PSPREL_P (int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  UNW_DEC_SPILL_SPREL_P (int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  X3 ; 
 int /*<<< orphan*/  unw_decode_uleb128 (unsigned char**) ; 

__attribute__((used)) static unsigned char *
unw_decode_x3 (unsigned char *dp, unsigned char code, void *arg)
{
  unsigned char byte1, byte2, abreg, qp;
  unw_word t, off;

  byte1 = *dp++; byte2 = *dp++;
  t = unw_decode_uleb128 (&dp);
  off = unw_decode_uleb128 (&dp);

  qp = (byte1 & 0x3f);
  abreg = (byte2 & 0x7f);

  if (byte1 & 0x80)
    UNW_DEC_SPILL_SPREL_P(X3, qp, t, abreg, off, arg);
  else
    UNW_DEC_SPILL_PSPREL_P(X3, qp, t, abreg, off, arg);
  return dp;
}