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
struct TYPE_3__ {char* ident; } ;
typedef  TYPE_1__ frontend_ctx_driver_t ;
typedef  enum frontend_architecture { ____Placeholder_frontend_architecture } frontend_architecture ;
typedef  int /*<<< orphan*/  architecture ;

/* Variables and functions */
#define  FRONTEND_ARCH_ARM 136 
#define  FRONTEND_ARCH_ARMV7 135 
#define  FRONTEND_ARCH_ARMV8 134 
#define  FRONTEND_ARCH_MIPS 133 
#define  FRONTEND_ARCH_NONE 132 
#define  FRONTEND_ARCH_PPC 131 
#define  FRONTEND_ARCH_TILE 130 
#define  FRONTEND_ARCH_X86 129 
#define  FRONTEND_ARCH_X86_64 128 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_NOT_AVAILABLE ; 
 int PATH_MAX_LENGTH ; 
 int frontend_driver_get_cpu_architecture () ; 
 TYPE_1__* frontend_get_ptr () ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

void netplay_get_architecture(char *frontend_architecture, size_t size)
{
   const frontend_ctx_driver_t
      *frontend                  = frontend_get_ptr();
   enum frontend_architecture arch = frontend_driver_get_cpu_architecture();
   char architecture[PATH_MAX_LENGTH];

   switch (arch)
   {
      case FRONTEND_ARCH_X86:
         strlcpy(architecture, "x86", sizeof(architecture));
         break;
      case FRONTEND_ARCH_X86_64:
         strlcpy(architecture, "x64", sizeof(architecture));
         break;
      case FRONTEND_ARCH_PPC:
         strlcpy(architecture, "PPC", sizeof(architecture));
         break;
      case FRONTEND_ARCH_ARM:
         strlcpy(architecture, "ARM", sizeof(architecture));
         break;
      case FRONTEND_ARCH_ARMV7:
         strlcpy(architecture, "ARMv7", sizeof(architecture));
         break;
      case FRONTEND_ARCH_ARMV8:
         strlcpy(architecture, "ARMv8", sizeof(architecture));
         break;
      case FRONTEND_ARCH_MIPS:
         strlcpy(architecture, "MIPS", sizeof(architecture));
         break;
      case FRONTEND_ARCH_TILE:
         strlcpy(architecture, "Tilera", sizeof(architecture));
         break;
      case FRONTEND_ARCH_NONE:
      default:
         strlcpy(architecture,
               msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NOT_AVAILABLE),
               sizeof(architecture));
         break;
   }
   snprintf(frontend_architecture, size, "%s %s", frontend->ident, architecture);
}