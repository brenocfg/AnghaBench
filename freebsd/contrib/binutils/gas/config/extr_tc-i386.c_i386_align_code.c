#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* fr_literal; int fr_fix; int fr_var; } ;
typedef  TYPE_1__ fragS ;

/* Variables and functions */
 scalar_t__ CODE_16BIT ; 
 scalar_t__ CODE_64BIT ; 
 int Cpu686 ; 
#define  PROCESSOR_AMDFAM10 141 
#define  PROCESSOR_ATHLON 140 
#define  PROCESSOR_CORE 139 
#define  PROCESSOR_CORE2 138 
#define  PROCESSOR_GENERIC32 137 
#define  PROCESSOR_GENERIC64 136 
#define  PROCESSOR_I486 135 
#define  PROCESSOR_K6 134 
#define  PROCESSOR_K8 133 
#define  PROCESSOR_NOCONA 132 
#define  PROCESSOR_PENTIUM 131 
#define  PROCESSOR_PENTIUM4 130 
#define  PROCESSOR_PENTIUMPRO 129 
#define  PROCESSOR_UNKNOWN 128 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ cpu_arch_isa ; 
 int cpu_arch_isa_flags ; 
 int cpu_arch_tune ; 
 scalar_t__ flag_code ; 
 int /*<<< orphan*/  memcpy (int*,char const* const,int) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 

void
i386_align_code (fragS *fragP, int count)
{
  /* Various efficient no-op patterns for aligning code labels.
     Note: Don't try to assemble the instructions in the comments.
     0L and 0w are not legal.  */
  static const char f32_1[] =
    {0x90};					/* nop			*/
  static const char f32_2[] =
    {0x66,0x90};				/* xchg %ax,%ax */
  static const char f32_3[] =
    {0x8d,0x76,0x00};				/* leal 0(%esi),%esi	*/
  static const char f32_4[] =
    {0x8d,0x74,0x26,0x00};			/* leal 0(%esi,1),%esi	*/
  static const char f32_5[] =
    {0x90,					/* nop			*/
     0x8d,0x74,0x26,0x00};			/* leal 0(%esi,1),%esi	*/
  static const char f32_6[] =
    {0x8d,0xb6,0x00,0x00,0x00,0x00};		/* leal 0L(%esi),%esi	*/
  static const char f32_7[] =
    {0x8d,0xb4,0x26,0x00,0x00,0x00,0x00};	/* leal 0L(%esi,1),%esi */
  static const char f32_8[] =
    {0x90,					/* nop			*/
     0x8d,0xb4,0x26,0x00,0x00,0x00,0x00};	/* leal 0L(%esi,1),%esi */
  static const char f32_9[] =
    {0x89,0xf6,					/* movl %esi,%esi	*/
     0x8d,0xbc,0x27,0x00,0x00,0x00,0x00};	/* leal 0L(%edi,1),%edi */
  static const char f32_10[] =
    {0x8d,0x76,0x00,				/* leal 0(%esi),%esi	*/
     0x8d,0xbc,0x27,0x00,0x00,0x00,0x00};	/* leal 0L(%edi,1),%edi */
  static const char f32_11[] =
    {0x8d,0x74,0x26,0x00,			/* leal 0(%esi,1),%esi	*/
     0x8d,0xbc,0x27,0x00,0x00,0x00,0x00};	/* leal 0L(%edi,1),%edi */
  static const char f32_12[] =
    {0x8d,0xb6,0x00,0x00,0x00,0x00,		/* leal 0L(%esi),%esi	*/
     0x8d,0xbf,0x00,0x00,0x00,0x00};		/* leal 0L(%edi),%edi	*/
  static const char f32_13[] =
    {0x8d,0xb6,0x00,0x00,0x00,0x00,		/* leal 0L(%esi),%esi	*/
     0x8d,0xbc,0x27,0x00,0x00,0x00,0x00};	/* leal 0L(%edi,1),%edi */
  static const char f32_14[] =
    {0x8d,0xb4,0x26,0x00,0x00,0x00,0x00,	/* leal 0L(%esi,1),%esi */
     0x8d,0xbc,0x27,0x00,0x00,0x00,0x00};	/* leal 0L(%edi,1),%edi */
  static const char f32_15[] =
    {0xeb,0x0d,0x90,0x90,0x90,0x90,0x90,	/* jmp .+15; lotsa nops	*/
     0x90,0x90,0x90,0x90,0x90,0x90,0x90,0x90};
  static const char f16_3[] =
    {0x8d,0x74,0x00};				/* lea 0(%esi),%esi	*/
  static const char f16_4[] =
    {0x8d,0xb4,0x00,0x00};			/* lea 0w(%si),%si	*/
  static const char f16_5[] =
    {0x90,					/* nop			*/
     0x8d,0xb4,0x00,0x00};			/* lea 0w(%si),%si	*/
  static const char f16_6[] =
    {0x89,0xf6,					/* mov %si,%si		*/
     0x8d,0xbd,0x00,0x00};			/* lea 0w(%di),%di	*/
  static const char f16_7[] =
    {0x8d,0x74,0x00,				/* lea 0(%si),%si	*/
     0x8d,0xbd,0x00,0x00};			/* lea 0w(%di),%di	*/
  static const char f16_8[] =
    {0x8d,0xb4,0x00,0x00,			/* lea 0w(%si),%si	*/
     0x8d,0xbd,0x00,0x00};			/* lea 0w(%di),%di	*/
  static const char *const f32_patt[] = {
    f32_1, f32_2, f32_3, f32_4, f32_5, f32_6, f32_7, f32_8,
    f32_9, f32_10, f32_11, f32_12, f32_13, f32_14, f32_15
  };
  static const char *const f16_patt[] = {
    f32_1, f32_2, f16_3, f16_4, f16_5, f16_6, f16_7, f16_8,
    f32_15, f32_15, f32_15, f32_15, f32_15, f32_15, f32_15
  };
  /* nopl (%[re]ax) */
  static const char alt_3[] =
    {0x0f,0x1f,0x00};
  /* nopl 0(%[re]ax) */
  static const char alt_4[] =
    {0x0f,0x1f,0x40,0x00};
  /* nopl 0(%[re]ax,%[re]ax,1) */
  static const char alt_5[] =
    {0x0f,0x1f,0x44,0x00,0x00};
  /* nopw 0(%[re]ax,%[re]ax,1) */
  static const char alt_6[] =
    {0x66,0x0f,0x1f,0x44,0x00,0x00};
  /* nopl 0L(%[re]ax) */
  static const char alt_7[] =
    {0x0f,0x1f,0x80,0x00,0x00,0x00,0x00};
  /* nopl 0L(%[re]ax,%[re]ax,1) */
  static const char alt_8[] =
    {0x0f,0x1f,0x84,0x00,0x00,0x00,0x00,0x00};
  /* nopw 0L(%[re]ax,%[re]ax,1) */
  static const char alt_9[] =
    {0x66,0x0f,0x1f,0x84,0x00,0x00,0x00,0x00,0x00};
  /* nopw %cs:0L(%[re]ax,%[re]ax,1) */
  static const char alt_10[] =
    {0x66,0x2e,0x0f,0x1f,0x84,0x00,0x00,0x00,0x00,0x00};
  /* data16
     nopw %cs:0L(%[re]ax,%[re]ax,1) */
  static const char alt_long_11[] =
    {0x66,
     0x66,0x2e,0x0f,0x1f,0x84,0x00,0x00,0x00,0x00,0x00};
  /* data16
     data16
     nopw %cs:0L(%[re]ax,%[re]ax,1) */
  static const char alt_long_12[] =
    {0x66,
     0x66,
     0x66,0x2e,0x0f,0x1f,0x84,0x00,0x00,0x00,0x00,0x00};
  /* data16
     data16
     data16
     nopw %cs:0L(%[re]ax,%[re]ax,1) */
  static const char alt_long_13[] =
    {0x66,
     0x66,
     0x66,
     0x66,0x2e,0x0f,0x1f,0x84,0x00,0x00,0x00,0x00,0x00};
  /* data16
     data16
     data16
     data16
     nopw %cs:0L(%[re]ax,%[re]ax,1) */
  static const char alt_long_14[] =
    {0x66,
     0x66,
     0x66,
     0x66,
     0x66,0x2e,0x0f,0x1f,0x84,0x00,0x00,0x00,0x00,0x00};
  /* data16
     data16
     data16
     data16
     data16
     nopw %cs:0L(%[re]ax,%[re]ax,1) */
  static const char alt_long_15[] =
    {0x66,
     0x66,
     0x66,
     0x66,
     0x66,
     0x66,0x2e,0x0f,0x1f,0x84,0x00,0x00,0x00,0x00,0x00};
  /* nopl 0(%[re]ax,%[re]ax,1)
     nopw 0(%[re]ax,%[re]ax,1) */
  static const char alt_short_11[] =
    {0x0f,0x1f,0x44,0x00,0x00,
     0x66,0x0f,0x1f,0x44,0x00,0x00};
  /* nopw 0(%[re]ax,%[re]ax,1)
     nopw 0(%[re]ax,%[re]ax,1) */
  static const char alt_short_12[] =
    {0x66,0x0f,0x1f,0x44,0x00,0x00,
     0x66,0x0f,0x1f,0x44,0x00,0x00};
  /* nopw 0(%[re]ax,%[re]ax,1)
     nopl 0L(%[re]ax) */
  static const char alt_short_13[] =
    {0x66,0x0f,0x1f,0x44,0x00,0x00,
     0x0f,0x1f,0x80,0x00,0x00,0x00,0x00};
  /* nopl 0L(%[re]ax)
     nopl 0L(%[re]ax) */
  static const char alt_short_14[] =
    {0x0f,0x1f,0x80,0x00,0x00,0x00,0x00,
     0x0f,0x1f,0x80,0x00,0x00,0x00,0x00};
  /* nopl 0L(%[re]ax)
     nopl 0L(%[re]ax,%[re]ax,1) */
  static const char alt_short_15[] =
    {0x0f,0x1f,0x80,0x00,0x00,0x00,0x00,
     0x0f,0x1f,0x84,0x00,0x00,0x00,0x00,0x00};
  static const char *const alt_short_patt[] = {
    f32_1, f32_2, alt_3, alt_4, alt_5, alt_6, alt_7, alt_8,
    alt_9, alt_10, alt_short_11, alt_short_12, alt_short_13,
    alt_short_14, alt_short_15
  };
  static const char *const alt_long_patt[] = {
    f32_1, f32_2, alt_3, alt_4, alt_5, alt_6, alt_7, alt_8,
    alt_9, alt_10, alt_long_11, alt_long_12, alt_long_13,
    alt_long_14, alt_long_15
  };

  if (count <= 0 || count > 15)
    return;

  /* We need to decide which NOP sequence to use for 32bit and
     64bit. When -mtune= is used:

     1. For PROCESSOR_I486, PROCESSOR_PENTIUM and PROCESSOR_GENERIC32,
     f32_patt will be used.
     2. For PROCESSOR_K8 and PROCESSOR_AMDFAM10 in 64bit, NOPs with
     0x66 prefix will be used.
     3. For PROCESSOR_CORE2, alt_long_patt will be used.
     4. For PROCESSOR_PENTIUMPRO, PROCESSOR_PENTIUM4, PROCESSOR_NOCONA,
     PROCESSOR_CORE, PROCESSOR_CORE2, PROCESSOR_K6, PROCESSOR_ATHLON
     and PROCESSOR_GENERIC64, alt_short_patt will be used.

     When -mtune= isn't used, alt_short_patt will be used if
     cpu_arch_isa_flags has Cpu686. Otherwise, f32_patt will be used.

     When -march= or .arch is used, we can't use anything beyond
     cpu_arch_isa_flags.   */

  if (flag_code == CODE_16BIT)
    {
      memcpy (fragP->fr_literal + fragP->fr_fix,
	      f16_patt[count - 1], count);
      if (count > 8)
	/* Adjust jump offset.  */
	fragP->fr_literal[fragP->fr_fix + 1] = count - 2;
    }
  else if (flag_code == CODE_64BIT && cpu_arch_tune == PROCESSOR_K8)
    {
      int i;
      int nnops = (count + 3) / 4;
      int len = count / nnops;
      int remains = count - nnops * len;
      int pos = 0;

      /* The recommended way to pad 64bit code is to use NOPs preceded
	 by maximally four 0x66 prefixes.  Balance the size of nops.  */
      for (i = 0; i < remains; i++)
	{
	  memset (fragP->fr_literal + fragP->fr_fix + pos, 0x66, len);
	  fragP->fr_literal[fragP->fr_fix + pos + len] = 0x90;
	  pos += len + 1;
	}
      for (; i < nnops; i++)
	{
	  memset (fragP->fr_literal + fragP->fr_fix + pos, 0x66, len - 1);
	  fragP->fr_literal[fragP->fr_fix + pos + len - 1] = 0x90;
	  pos += len;
	}
    }
  else
    {
      const char *const *patt = NULL;

      if (cpu_arch_isa == PROCESSOR_UNKNOWN)
	{
	  /* PROCESSOR_UNKNOWN means that all ISAs may be used.  */
	  switch (cpu_arch_tune)
	    {
	    case PROCESSOR_UNKNOWN:
	      /* We use cpu_arch_isa_flags to check if we SHOULD
		 optimize for Cpu686.  */
	      if ((cpu_arch_isa_flags & Cpu686) != 0)
		patt = alt_short_patt;
	      else
		patt = f32_patt;
	      break;
	    case PROCESSOR_CORE2:
	      patt = alt_long_patt;
	      break;
	    case PROCESSOR_PENTIUMPRO:
	    case PROCESSOR_PENTIUM4:
	    case PROCESSOR_NOCONA:
	    case PROCESSOR_CORE:
	    case PROCESSOR_K6:
	    case PROCESSOR_ATHLON:
	    case PROCESSOR_K8:
	    case PROCESSOR_GENERIC64:
	    case PROCESSOR_AMDFAM10:
	      patt = alt_short_patt;
	      break;
	    case PROCESSOR_I486:
	    case PROCESSOR_PENTIUM:
	    case PROCESSOR_GENERIC32:
	      patt = f32_patt;
	      break;
	    }
	}
      else
	{
	  switch (cpu_arch_tune)
	    {
	    case PROCESSOR_UNKNOWN:
	      /* When cpu_arch_isa is net, cpu_arch_tune shouldn't be
		 PROCESSOR_UNKNOWN.  */
	      abort ();
	      break;

	    case PROCESSOR_I486:
	    case PROCESSOR_PENTIUM:
	    case PROCESSOR_PENTIUMPRO:
	    case PROCESSOR_PENTIUM4:
	    case PROCESSOR_NOCONA:
	    case PROCESSOR_CORE:
	    case PROCESSOR_K6:
	    case PROCESSOR_ATHLON:
	    case PROCESSOR_K8:
	    case PROCESSOR_AMDFAM10:
	    case PROCESSOR_GENERIC32:
	      /* We use cpu_arch_isa_flags to check if we CAN optimize
		 for Cpu686.  */
	      if ((cpu_arch_isa_flags & Cpu686) != 0)
		patt = alt_short_patt;
	      else
		patt = f32_patt;
	      break;
	    case PROCESSOR_CORE2:
	      if ((cpu_arch_isa_flags & Cpu686) != 0)
		patt = alt_long_patt;
	      else
		patt = f32_patt;
	      break;
	    case PROCESSOR_GENERIC64:
	      patt = alt_short_patt;
	      break;
	    }
	}

      memcpy (fragP->fr_literal + fragP->fr_fix,
	      patt[count - 1], count);
    }
  fragP->fr_var = count;
}