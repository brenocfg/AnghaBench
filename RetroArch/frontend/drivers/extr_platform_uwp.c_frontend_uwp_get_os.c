#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buildStr ;
struct TYPE_10__ {int dwOSVersionInfoSize; int dwMajorVersion; int dwMinorVersion; char* szCSDVersion; int /*<<< orphan*/  dwPlatformId; int /*<<< orphan*/  dwBuildNumber; int /*<<< orphan*/  member_0; } ;
struct TYPE_9__ {int dwOSVersionInfoSize; scalar_t__ wProductType; int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int wProcessorArchitecture; TYPE_1__ member_0; } ;
typedef  TYPE_2__ SYSTEM_INFO ;
typedef  TYPE_3__ OSVERSIONINFOEX ;
typedef  TYPE_4__ OSVERSIONINFO ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetSystemInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  GetVersionEx (TYPE_4__*) ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
#define  PROCESSOR_ARCHITECTURE_AMD64 130 
#define  PROCESSOR_ARCHITECTURE_ARM 129 
#define  PROCESSOR_ARCHITECTURE_INTEL 128 
 scalar_t__ VER_NT_WORKSTATION ; 
 int /*<<< orphan*/  VER_PLATFORM_WIN32_NT ; 
 int /*<<< orphan*/  VER_PLATFORM_WIN32_WINDOWS ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,int,...) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  string_is_equal (char const*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char const*,size_t) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 
 char* uwp_device_family ; 

__attribute__((used)) static void frontend_uwp_get_os(char *s, size_t len, int *major, int *minor)
{
   char buildStr[11]      = {0};
   bool server            = false;
   const char *arch       = "";

#if defined(_WIN32_WINNT) && _WIN32_WINNT >= 0x0500
   /* Windows 2000 and later */
   SYSTEM_INFO si         = {{0}};
   OSVERSIONINFOEX vi     = {0};
   vi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

   GetSystemInfo(&si);

   /* Available from NT 3.5 and Win95 */
   GetVersionEx((OSVERSIONINFO*)&vi);

   server = vi.wProductType != VER_NT_WORKSTATION;

   switch (si.wProcessorArchitecture)
   {
      case PROCESSOR_ARCHITECTURE_AMD64:
         arch = "x64";
         break;
      case PROCESSOR_ARCHITECTURE_INTEL:
         arch = "x86";
         break;
      case PROCESSOR_ARCHITECTURE_ARM:
         arch = "ARM";
         break;
      default:
         break;
   }
#else
   OSVERSIONINFO vi = {0};
   vi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

   /* Available from NT 3.5 and Win95 */
   GetVersionEx(&vi);
#endif

   if (major)
      *major = vi.dwMajorVersion;

   if (minor)
      *minor = vi.dwMinorVersion;

   if (vi.dwMajorVersion == 4 && vi.dwMinorVersion == 0)
      snprintf(buildStr, sizeof(buildStr), "%lu", (DWORD)(LOWORD(vi.dwBuildNumber))); /* Windows 95 build number is in the low-order word only */
   else
      snprintf(buildStr, sizeof(buildStr), "%lu", vi.dwBuildNumber);

   switch (vi.dwMajorVersion)
   {
      case 10:
         if (server)
            strlcpy(s, "Windows Server 2016", len);
         else
            strlcpy(s, "Windows 10", len);
         break;
      case 6:
         switch (vi.dwMinorVersion)
         {
            case 3:
               if (server)
                  strlcpy(s, "Windows Server 2012 R2", len);
               else
                  strlcpy(s, "Windows 8.1", len);
               break;
            case 2:
               if (server)
                  strlcpy(s, "Windows Server 2012", len);
               else
                  strlcpy(s, "Windows 8", len);
               break;
            case 1:
               if (server)
                  strlcpy(s, "Windows Server 2008 R2", len);
               else
                  strlcpy(s, "Windows 7", len);
               break;
            case 0:
               if (server)
                  strlcpy(s, "Windows Server 2008", len);
               else
                  strlcpy(s, "Windows Vista", len);
               break;
            default:
               break;
         }
         break;
      case 5:
         switch (vi.dwMinorVersion)
         {
            case 2:
               if (server)
                  strlcpy(s, "Windows Server 2003", len);
               else
               {
                  /* Yes, XP Pro x64 is a higher version number than XP x86 */
                  if (string_is_equal(arch, "x64"))
                     strlcpy(s, "Windows XP", len);
               }
               break;
            case 1:
               strlcpy(s, "Windows XP", len);
               break;
            case 0:
               strlcpy(s, "Windows 2000", len);
               break;
         }
         break;
      case 4:
         switch (vi.dwMinorVersion)
         {
            case 0:
               if (vi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
                  strlcpy(s, "Windows 95", len);
               else if (vi.dwPlatformId == VER_PLATFORM_WIN32_NT)
                  strlcpy(s, "Windows NT 4.0", len);
               else
                  strlcpy(s, "Unknown", len);
               break;
            case 90:
               strlcpy(s, "Windows ME", len);
               break;
            case 10:
               strlcpy(s, "Windows 98", len);
               break;
         }
         break;
      default:
         snprintf(s, len, "Windows %i.%i", *major, *minor);
         break;
   }

   if (!string_is_empty(arch))
   {
      strlcat(s, " ", len);
      strlcat(s, arch, len);
   }

   strlcat(s, " Build ", len);
   strlcat(s, buildStr, len);

   if (!string_is_empty(vi.szCSDVersion))
   {
      strlcat(s, " ", len);
      strlcat(s, vi.szCSDVersion, len);
   }

   if (!string_is_empty(uwp_device_family))
   {
      strlcat(s, " ", len);
      strlcat(s, uwp_device_family, len);
   }
}