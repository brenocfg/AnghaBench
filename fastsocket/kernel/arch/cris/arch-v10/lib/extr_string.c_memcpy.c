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
 int MEMCPY_BY_BLOCK_THRESHOLD ; 

void *
memcpy(void *pdst, const void *psrc, size_t pn)
{
  /* Now we want the parameters put in special registers.
     Make sure the compiler is able to make something useful of this.
     As it is now: r10 -> r13; r11 -> r11 (nop); r12 -> r12 (nop).

     If gcc was allright, it really would need no temporaries, and no
     stack space to save stuff on.  */

  register void *return_dst __asm__ ("r10") = pdst;
  register unsigned char *dst __asm__ ("r13") = pdst;
  register unsigned const char *src __asm__ ("r11") = psrc;
  register int n __asm__ ("r12") = pn;

  /* When src is aligned but not dst, this makes a few extra needless
     cycles.  I believe it would take as many to check that the
     re-alignment was unnecessary.  */
  if (((unsigned long) dst & 3) != 0
      /* Don't align if we wouldn't copy more than a few bytes; so we
	 don't have to check further for overflows.  */
      && n >= 3)
  {
    if ((unsigned long) dst & 1)
      {
	n--;
	*dst = *src;
	src++;
	dst++;
      }

    if ((unsigned long) dst & 2)
      {
	n -= 2;
	*(short *) dst = *(short *) src;
	src += 2;
	dst += 2;
      }
  }

  /* Decide which copying method to use.  */
  if (n >= MEMCPY_BY_BLOCK_THRESHOLD)
    {
      /* It is not optimal to tell the compiler about clobbering any
	 registers; that will move the saving/restoring of those registers
	 to the function prologue/epilogue, and make non-movem sizes
	 suboptimal.  */
      __asm__ volatile
	("\
	 ;; GCC does promise correct register allocations, but let's	\n\
	 ;; make sure it keeps its promises.				\n\
	 .ifnc %0-%1-%2,$r13-$r11-$r12					\n\
	 .error \"GCC reg alloc bug: %0-%1-%4 != $r13-$r12-$r11\"	\n\
	 .endif								\n\
									\n\
	 ;; Save the registers we'll use in the movem process		\n\
	 ;; on the stack.						\n\
	 subq	11*4,sp							\n\
	 movem	r10,[sp]						\n\
									\n\
	 ;; Now we've got this:						\n\
	 ;; r11 - src							\n\
	 ;; r13 - dst							\n\
	 ;; r12 - n							\n\
									\n\
	 ;; Update n for the first loop.				\n\
	 subq	 44,r12							\n\
0:									\n\
"
#ifdef __arch_common_v10_v32
	 /* Cater to branch offset difference between v32 and v10.  We
	    assume the branch below has an 8-bit offset.  */
"	 setf\n"
#endif
"	 movem	[r11+],r10						\n\
	 subq	44,r12							\n\
	 bge	 0b							\n\
	 movem	r10,[r13+]						\n\
									\n\
	 ;; Compensate for last loop underflowing n.			\n\
	 addq	44,r12							\n\
									\n\
	 ;; Restore registers from stack.				\n\
	 movem [sp+],r10"

	 /* Outputs.  */
	 : "=r" (dst), "=r" (src), "=r" (n)

	 /* Inputs.  */
	 : "0" (dst), "1" (src), "2" (n));
    }

  while (n >= 16)
    {
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(long *) dst = *(long *) src; dst += 4; src += 4;

      n -= 16;
    }

  switch (n)
    {
    case 0:
      break;

    case 1:
      *dst = *src;
      break;

    case 2:
      *(short *) dst = *(short *) src;
      break;

    case 3:
      *(short *) dst = *(short *) src; dst += 2; src += 2;
      *dst = *src;
      break;

    case 4:
      *(long *) dst = *(long *) src;
      break;

    case 5:
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *dst = *src;
      break;

    case 6:
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(short *) dst = *(short *) src;
      break;

    case 7:
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(short *) dst = *(short *) src; dst += 2; src += 2;
      *dst = *src;
      break;

    case 8:
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(long *) dst = *(long *) src;
      break;

    case 9:
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *dst = *src;
      break;

    case 10:
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(short *) dst = *(short *) src;
      break;

    case 11:
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(short *) dst = *(short *) src; dst += 2; src += 2;
      *dst = *src;
      break;

    case 12:
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(long *) dst = *(long *) src;
      break;

    case 13:
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *dst = *src;
      break;

    case 14:
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(short *) dst = *(short *) src;
      break;

    case 15:
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(long *) dst = *(long *) src; dst += 4; src += 4;
      *(short *) dst = *(short *) src; dst += 2; src += 2;
      *dst = *src;
      break;
    }

  return return_dst;
}