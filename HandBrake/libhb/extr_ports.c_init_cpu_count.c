#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint8_t ;
struct TYPE_5__ {int cpu_count; } ;
typedef  TYPE_1__ system_info ;
typedef  int processorid_t ;
typedef  int /*<<< orphan*/  p_aff ;
typedef  int /*<<< orphan*/  cpu_set_t ;
typedef  int /*<<< orphan*/  cpu_count ;
struct TYPE_6__ {int dwNumberOfProcessors; } ;
typedef  TYPE_2__ SYSTEM_INFO ;

/* Variables and functions */
 int CTL_HW ; 
 int /*<<< orphan*/  GetSystemInfo (TYPE_2__*) ; 
 int HW_NCPU ; 
 int MAX (int,int) ; 
 int MIN (int,int) ; 
 int /*<<< orphan*/  P_STATUS ; 
 int /*<<< orphan*/  _SC_CPUID_MAX ; 
 int /*<<< orphan*/  get_system_info (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int p_online (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_getaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 scalar_t__ sysctl (int*,int,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_cpu_count()
{
    int cpu_count = 1;

#if defined(SYS_CYGWIN) || defined(SYS_MINGW)
    SYSTEM_INFO cpuinfo;
    GetSystemInfo( &cpuinfo );
    cpu_count = cpuinfo.dwNumberOfProcessors;

#elif defined(SYS_LINUX)
    unsigned int bit;
    cpu_set_t p_aff;
    memset( &p_aff, 0, sizeof(p_aff) );
    sched_getaffinity( 0, sizeof(p_aff), &p_aff );
    for( cpu_count = 0, bit = 0; bit < sizeof(p_aff); bit++ )
         cpu_count += (((uint8_t *)&p_aff)[bit / 8] >> (bit % 8)) & 1;

#elif defined(SYS_BEOS)
    system_info info;
    get_system_info( &info );
    cpu_count = info.cpu_count;

#elif defined(SYS_DARWIN) || defined(SYS_FREEBSD) || defined(SYS_OPENBSD)
    size_t length = sizeof( cpu_count );
#ifdef SYS_OPENBSD
    int mib[2] = { CTL_HW, HW_NCPU };
    if( sysctl(mib, 2, &cpu_count, &length, NULL, 0) )
#else
    if( sysctlbyname("hw.ncpu", &cpu_count, &length, NULL, 0) )
#endif
    {
        cpu_count = 1;
    }

#elif defined( SYS_SunOS )
    {
        processorid_t cpumax;
        int i,j=0;

        cpumax = sysconf(_SC_CPUID_MAX);

        for(i = 0; i <= cpumax; i++ )
        {
            if(p_online(i, P_STATUS) != -1)
            {
                j++;
            }
        }
        cpu_count=j;
    }
#endif

    cpu_count = MAX( 1, cpu_count );
    cpu_count = MIN( cpu_count, 64 );

    return cpu_count;
}