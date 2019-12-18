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
 int /*<<< orphan*/  R3 ; 
 int /*<<< orphan*/  UNW_DEC_PROLOGUE (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  unw_decode_uleb128 (unsigned char**) ; 

__attribute__((used)) static unsigned char *
unw_decode_r3 (unsigned char *dp, unsigned char code, void *arg)
{
  unw_word rlen;

  rlen = unw_decode_uleb128 (&dp);
  UNW_DEC_PROLOGUE(R3, ((code & 0x3) == 1), rlen, arg);
  return dp;
}