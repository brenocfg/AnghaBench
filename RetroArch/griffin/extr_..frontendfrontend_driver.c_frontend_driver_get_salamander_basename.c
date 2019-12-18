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
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

bool frontend_driver_get_salamander_basename(char *s, size_t len)
{
#ifdef HAVE_DYNAMIC
   return false;
#else

#if defined(__CELLOS_LV2__)
   strlcpy(s, "EBOOT.BIN", len);
   return true;
#elif defined(PSP)
   strlcpy(s, "EBOOT.PBP", len);
   return true;
#elif defined(VITA)
   strlcpy(s, "eboot.bin", len);
   return true;
#elif defined(PS2)
   strlcpy(s, "eboot.elf", len);
   return true;
#elif defined(_XBOX1)
   strlcpy(s, "default.xbe", len);
   return true;
#elif defined(_XBOX360)
   strlcpy(s, "default.xex", len);
   return true;
#elif defined(HW_RVL)
   strlcpy(s, "boot.dol", len);
   return true;
#elif defined(HW_WUP)
   strlcpy(s, "retroarch.rpx", len);
   return true;
#elif defined(_3DS)
   strlcpy(s, "retroarch.core", len);
   return true;
#elif defined(SWITCH)
   strlcpy(s, "retroarch_switch.nro", len);
   return true;
#else
   return false;
#endif

#endif
}