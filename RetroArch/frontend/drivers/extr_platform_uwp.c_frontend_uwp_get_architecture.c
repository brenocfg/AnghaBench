#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  enum frontend_architecture { ____Placeholder_frontend_architecture } frontend_architecture ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int wProcessorArchitecture; TYPE_1__ member_0; } ;
typedef  TYPE_2__ SYSTEM_INFO ;

/* Variables and functions */
 int FRONTEND_ARCH_ARM ; 
 int FRONTEND_ARCH_NONE ; 
 int FRONTEND_ARCH_X86 ; 
 int FRONTEND_ARCH_X86_64 ; 
 int /*<<< orphan*/  GetSystemInfo (TYPE_2__*) ; 
#define  PROCESSOR_ARCHITECTURE_AMD64 130 
#define  PROCESSOR_ARCHITECTURE_ARM 129 
#define  PROCESSOR_ARCHITECTURE_INTEL 128 

enum frontend_architecture frontend_uwp_get_architecture(void)
{
#if defined(_WIN32_WINNT) && _WIN32_WINNT >= 0x0500
   /* Windows 2000 and later */
   SYSTEM_INFO si = {{0}};

   GetSystemInfo(&si);

   switch (si.wProcessorArchitecture)
   {
      case PROCESSOR_ARCHITECTURE_AMD64:
         return FRONTEND_ARCH_X86_64;
         break;
      case PROCESSOR_ARCHITECTURE_INTEL:
         return FRONTEND_ARCH_X86;
         break;
      case PROCESSOR_ARCHITECTURE_ARM:
         return FRONTEND_ARCH_ARM;
         break;
      default:
         break;
   }
#endif

   return FRONTEND_ARCH_NONE;
}