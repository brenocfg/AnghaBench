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
 int /*<<< orphan*/  B3 ; 
 int /*<<< orphan*/  B4 ; 
 int /*<<< orphan*/  UNW_DEC_BAD_CODE (unsigned char) ; 
 int /*<<< orphan*/  UNW_DEC_COPY_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  UNW_DEC_EPILOGUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  UNW_DEC_LABEL_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  unw_decode_uleb128 (unsigned char**) ; 
 unsigned char* unw_decode_x1 (unsigned char*,unsigned char,void*) ; 
 unsigned char* unw_decode_x2 (unsigned char*,unsigned char,void*) ; 
 unsigned char* unw_decode_x3 (unsigned char*,unsigned char,void*) ; 
 unsigned char* unw_decode_x4 (unsigned char*,unsigned char,void*) ; 

__attribute__((used)) static unsigned char *
unw_decode_b3_x4 (unsigned char *dp, unsigned char code, void *arg)
{
  unw_word t, ecount, label;

  if ((code & 0x10) == 0)
    {
      t = unw_decode_uleb128 (&dp);
      ecount = unw_decode_uleb128 (&dp);
      UNW_DEC_EPILOGUE(B3, t, ecount, arg);
    }
  else if ((code & 0x07) == 0)
    {
      label = unw_decode_uleb128 (&dp);
      if ((code & 0x08) != 0)
	UNW_DEC_COPY_STATE(B4, label, arg);
      else
	UNW_DEC_LABEL_STATE(B4, label, arg);
    }
  else
    switch (code & 0x7)
      {
      case 1: return unw_decode_x1 (dp, code, arg);
      case 2: return unw_decode_x2 (dp, code, arg);
      case 3: return unw_decode_x3 (dp, code, arg);
      case 4: return unw_decode_x4 (dp, code, arg);
      default: UNW_DEC_BAD_CODE(code); break;
      }
  return dp;
}