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
 scalar_t__ envIsHomebrew () ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

bool frontend_driver_get_core_extension(char *s, size_t len)
{
#ifdef HAVE_DYNAMIC

#ifdef _WIN32
   strlcpy(s, "dll", len);
   return true;
#elif defined(__APPLE__) || defined(__MACH__)
   strlcpy(s, "dylib", len);
   return true;
#else
   strlcpy(s, "so", len);
   return true;
#endif

#else

#if defined(__CELLOS_LV2__)
   strlcpy(s, "self|bin", len);
   return true;
#elif defined(PSP)
   strlcpy(s, "pbp", len);
   return true;
#elif defined(VITA)
   strlcpy(s, "self|bin", len);
   return true;
#elif defined(PS2)
   strlcpy(s, "elf", len);
   return true;
#elif defined(_XBOX1)
   strlcpy(s, "xbe", len);
   return true;
#elif defined(_XBOX360)
   strlcpy(s, "xex", len);
   return true;
#elif defined(GEKKO)
   strlcpy(s, "dol", len);
   return true;
#elif defined(HW_WUP)
   strlcpy(s, "rpx|elf", len);
   return true;
#elif defined(__linux__)
   strlcpy(s, "elf", len);
   return true;
#elif defined(HAVE_LIBNX)
   strlcpy(s, "nro", len);
   return true;
#elif defined(_3DS)
   if (envIsHomebrew())
      strlcpy(s, "3dsx", len);
   else
      strlcpy(s, "cia", len);
   return true;
#else
   return false;
#endif

#endif
}