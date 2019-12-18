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
typedef  int /*<<< orphan*/  z_off_t ;
typedef  int /*<<< orphan*/  voidpf ;
typedef  scalar_t__ uLong ;
typedef  int /*<<< orphan*/  uInt ;

/* Variables and functions */

uLong zlibCompileFlags(void)
{
   uLong flags;

   flags = 0;
   switch ((int)(sizeof(uInt))) {
      case 2:     break;
      case 4:     flags += 1;     break;
      case 8:     flags += 2;     break;
      default:    flags += 3;
   }
   switch ((int)(sizeof(uLong))) {
      case 2:     break;
      case 4:     flags += 1 << 2;        break;
      case 8:     flags += 2 << 2;        break;
      default:    flags += 3 << 2;
   }
   switch ((int)(sizeof(voidpf))) {
      case 2:     break;
      case 4:     flags += 1 << 4;        break;
      case 8:     flags += 2 << 4;        break;
      default:    flags += 3 << 4;
   }
   switch ((int)(sizeof(z_off_t))) {
      case 2:     break;
      case 4:     flags += 1 << 6;        break;
      case 8:     flags += 2 << 6;        break;
      default:    flags += 3 << 6;
   }
#ifdef DEBUG
   flags += 1 << 8;
#endif
#if defined(ASMV) || defined(ASMINF)
   flags += 1 << 9;
#endif
#ifdef ZLIB_WINAPI
   flags += 1 << 10;
#endif
#ifdef BUILDFIXED
   flags += 1 << 12;
#endif
#ifdef DYNAMIC_CRC_TABLE
   flags += 1 << 13;
#endif
#ifdef NO_GZCOMPRESS
   flags += 1L << 16;
#endif
#ifdef NO_GZIP
   flags += 1L << 17;
#endif
#ifdef PKZIP_BUG_WORKAROUND
   flags += 1L << 20;
#endif
#ifdef FASTEST
   flags += 1L << 21;
#endif
#if defined(STDC) || defined(Z_HAVE_STDARG_H)
#  ifdef NO_vsnprintf
   flags += 1L << 25;
#    ifdef HAS_vsprintf_void
   flags += 1L << 26;
#    endif
#  else
#    ifdef HAS_vsnprintf_void
   flags += 1L << 26;
#    endif
#  endif
#else
   flags += 1L << 24;
#  ifdef NO_snprintf
   flags += 1L << 25;
#    ifdef HAS_sprintf_void
   flags += 1L << 26;
#    endif
#  else
#    ifdef HAS_snprintf_void
   flags += 1L << 26;
#    endif
#  endif
#endif
   return flags;
}