#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vmstats ;
typedef  int /*<<< orphan*/  usermem ;
struct tbl_vmstats {double free_count; double pagesize; } ;
struct rminfo {double availrmem; } ;
struct pst_static {double page_size; } ;
struct pst_dynamic {double psd_free; } ;
struct TYPE_5__ {int dwLength; scalar_t__ ullAvailPhys; } ;
typedef  TYPE_1__ lMEMORYSTATUSEX ;
struct TYPE_6__ {scalar_t__ dwAvailPhys; } ;
typedef  int /*<<< orphan*/  (* PFN_MS_EX ) (TYPE_1__*) ;
typedef  TYPE_3__ MEMORYSTATUS ;
typedef  int /*<<< orphan*/  HMODULE ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int*) ; 
#define  CTL_HW 129 
 int /*<<< orphan*/  GetModuleHandle (char*) ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GlobalMemoryStatus (TYPE_3__*) ; 
#define  HW_USERMEM 128 
 int /*<<< orphan*/  MPSA_RMINFO ; 
 int /*<<< orphan*/  MP_SAGET ; 
 int /*<<< orphan*/  TBL_VMSTATS ; 
 int /*<<< orphan*/  _SC_AVPHYS_PAGES ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int physmem_total () ; 
 scalar_t__ pstat_getdynamic (struct pst_dynamic*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ pstat_getstatic (struct pst_static*,int,int,int /*<<< orphan*/ ) ; 
 double sysconf (int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl (int*,int /*<<< orphan*/ ,unsigned int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sysmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rminfo*,int) ; 
 int table (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tbl_vmstats*,int,int) ; 

double
physmem_available (void)
{
#if defined _SC_AVPHYS_PAGES && defined _SC_PAGESIZE
  { /* This works on linux-gnu, solaris2 and cygwin.  */
    double pages = sysconf (_SC_AVPHYS_PAGES);
    double pagesize = sysconf (_SC_PAGESIZE);
    if (0 <= pages && 0 <= pagesize)
      return pages * pagesize;
  }
#endif

#if HAVE_PSTAT_GETSTATIC && HAVE_PSTAT_GETDYNAMIC
  { /* This works on hpux11.  */
    struct pst_static pss;
    struct pst_dynamic psd;
    if (0 <= pstat_getstatic (&pss, sizeof pss, 1, 0)
	&& 0 <= pstat_getdynamic (&psd, sizeof psd, 1, 0))
      {
	double pages = psd.psd_free;
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
	double pages = realmem.availrmem;
	if (0 <= pages && 0 <= pagesize)
	  return pages * pagesize;
      }
  }
#endif

#if HAVE_TABLE && defined TBL_VMSTATS
  { /* This works on Tru64 UNIX V4/5.  */
    struct tbl_vmstats vmstats;

    if (table (TBL_VMSTATS, 0, &vmstats, 1, sizeof (vmstats)) == 1)
      {
	double pages = vmstats.free_count;
	double pagesize = vmstats.pagesize;

	if (0 <= pages && 0 <= pagesize)
	  return pages * pagesize;
      }
  }
#endif

#if HAVE_SYSCTL && defined HW_USERMEM
  { /* This works on *bsd and darwin.  */
    unsigned int usermem;
    size_t len = sizeof usermem;
    static int mib[2] = { CTL_HW, HW_USERMEM };

    if (sysctl (mib, ARRAY_SIZE (mib), &usermem, &len, NULL, 0) == 0
	&& len == sizeof (usermem))
      return (double) usermem;
  }
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
	return (double) lms_ex.ullAvailPhys;
      }

    /*  Fall back to GlobalMemoryStatus which is always available.
        but returns wrong results for physical memory > 4GB  */
    else
      {
	MEMORYSTATUS ms;
	GlobalMemoryStatus (&ms);
	return (double) ms.dwAvailPhys;
      }
  }
#endif

  /* Guess 25% of physical memory.  */
  return physmem_total () / 4;
}