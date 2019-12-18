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
 int /*<<< orphan*/  Com_Printf (char*,int,int) ; 
 int _FPU_DEFAULT ; 
 int /*<<< orphan*/  _FPU_GETCW (int) ; 
 int _FPU_MASK_IM ; 
 int _FPU_MASK_ZM ; 
 int /*<<< orphan*/  _FPU_SETCW (int) ; 
 int /*<<< orphan*/  assert (int) ; 

void    Sys_ConfigureFPU() { // bk001213 - divide by zero
#ifdef __linux__
#ifdef __i386
#ifndef NDEBUG

  // bk0101022 - enable FPE's in debug mode
  static int fpu_word = _FPU_DEFAULT & ~(_FPU_MASK_ZM | _FPU_MASK_IM);
  int current = 0;
  _FPU_GETCW(current);
  if ( current!=fpu_word)
  {
#if 0
    Com_Printf("FPU Control 0x%x (was 0x%x)\n", fpu_word, current );
    _FPU_SETCW( fpu_word );
    _FPU_GETCW( current );
    assert(fpu_word==current);
#endif
  }
#else // NDEBUG
  static int fpu_word = _FPU_DEFAULT;
  _FPU_SETCW( fpu_word );
#endif // NDEBUG
#endif // __i386 
#endif // __linux
}