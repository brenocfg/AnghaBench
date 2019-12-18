#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rminfo {double physmem; } ;
struct pst_static {double physical_memory; double page_size; } ;
typedef  int /*<<< orphan*/  physmem ;
struct TYPE_6__ {int dwLength; scalar_t__ ullTotalPhys; } ;
typedef  TYPE_1__ lMEMORYSTATUSEX ;
typedef  int /*<<< orphan*/  caddr_t ;
struct TYPE_8__ {double physmem; } ;
struct TYPE_7__ {scalar_t__ dwTotalPhys; } ;
typedef  int /*<<< orphan*/  (* PFN_MS_EX ) (TYPE_1__*) ;
typedef  TYPE_3__ MEMORYSTATUS ;
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
#define  CTL_HW 129 
 int /*<<< orphan*/  GSI_PHYSMEM ; 
 int /*<<< orphan*/  GetModuleHandle (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GlobalMemoryStatus (TYPE_3__*) ; 
#define  HW_PHYSMEM 128 
 int /*<<< orphan*/  MPSA_RMINFO ; 
 int /*<<< orphan*/  MP_SAGET ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  _SC_PHYS_PAGES ; 
 TYPE_4__ _system_configuration ; 
 int getsysinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ pstat_getstatic (struct pst_static*,int,int,int /*<<< orphan*/ ) ; 
 double sysconf (int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl (int*,int /*<<< orphan*/ ,unsigned int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sysmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rminfo*,int) ; 

double
physmem_total (void)
{
#if defined _SC_PHYS_PAGES && defined _SC_PAGESIZE
  { /* This works on linux-gnu, solaris2 and cygwin.  */
    double pages = sysconf (_SC_PHYS_PAGES);
    double pagesize = sysconf (_SC_PAGESIZE);
    if (0 <= pages && 0 <= pagesize)
      return pages * pagesize;
  }
#endif

#if HAVE_PSTAT_GETSTATIC
  { /* This works on hpux11.  */
    struct pst_static pss;
    if (0 <= pstat_getstatic (&pss, sizeof pss, 1, 0))
      {
	double pages = pss.physical_memory;
	double pagesize = pss.page_size;
	if (0 <= pages && 0 <= pagesize)
	  return pages * pagesize;
      }
  }
#endif

#if HAVE_SYSMP && defined MP_SAGET && defined MPSA_RMINFO && defined _SC_PAGESIZE
  { /* This works on irix6. */
    struct rminfo realmem;
    if (sysmp (MP_SAGET, MPSA_RMINFO, &realmem, sizeof realmem) == 0)
      {
	double pagesize = sysconf (_SC_PAGESIZE);
	double pages = realmem.physmem;
	if (0 <= pages && 0 <= pagesize)
	  return pages * pagesize;
      }
  }
#endif

#if HAVE_GETSYSINFO && defined GSI_PHYSMEM
  { /* This works on Tru64 UNIX V4/5.  */
    int physmem;

    if (getsysinfo (GSI_PHYSMEM, (caddr_t) &physmem, sizeof (physmem),
		    NULL, NULL, NULL) == 1)
      {
	double kbytes = physmem;

	if (0 <= kbytes)
	  return kbytes * 1024.0;
      }
  }
#endif

#if HAVE_SYSCTL && defined HW_PHYSMEM
  { /* This works on *bsd and darwin.  */
    unsigned int physmem;
    size_t len = sizeof physmem;
    static int mib[2] = { CTL_HW, HW_PHYSMEM };

    if (sysctl (mib, ARRAY_SIZE (mib), &physmem, &len, NULL, 0) == 0
	&& len == sizeof (physmem))
      return (double) physmem;
  }
#endif

#if HAVE__SYSTEM_CONFIGURATION
  /* This works on AIX 4.3.3+.  */
  return _system_configuration.physmem;
#endif

#if defined _WIN32
  { /* this works on windows */
    PFN_MS_EX pfnex;
    HMODULE h = GetModuleHandle ("kernel32.dll");

    if (!h)
      return 0.0;

    /*  Use GlobalMemoryStatusEx if available.  */
    if ((pfnex = (PFN_MS_EX) GetProcAddress (h, "GlobalMemoryStatusEx")))
      {
	lMEMORYSTATUSEX lms_ex;
	lms_ex.dwLength = sizeof lms_ex;
	if (!pfnex (&lms_ex))
	  return 0.0;
	return (double) lms_ex.ullTotalPhys;
      }

    /*  Fall back to GlobalMemoryStatus which is always available.
        but returns wrong results for physical memory > 4GB.  */
    else
      {
	MEMORYSTATUS ms;
	GlobalMemoryStatus (&ms);
	return (double) ms.dwTotalPhys;
      }
  }
#endif

  /* Return 0 if we can't determine the value.  */
  return 0;
}