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
 int /*<<< orphan*/  UNW_DEC_SPILL_PSPREL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  UNW_DEC_SPILL_SPREL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  X1 ; 
 int /*<<< orphan*/  unw_decode_uleb128 (unsigned char**) ; 

__attribute__((used)) static unsigned char *
unw_decode_x1 (unsigned char *dp,
	       unsigned char code __attribute__((unused)),
	       void *arg)
{
  unsigned char byte1, abreg;
  unw_word t, off;

  byte1 = *dp++;
  t = unw_decode_uleb128 (&dp);
  off = unw_decode_uleb128 (&dp);
  abreg = (byte1 & 0x7f);
  if (byte1 & 0x80)
	  UNW_DEC_SPILL_SPREL(X1, t, abreg, off, arg);
  else
	  UNW_DEC_SPILL_PSPREL(X1, t, abreg, off, arg);
  return dp;
}