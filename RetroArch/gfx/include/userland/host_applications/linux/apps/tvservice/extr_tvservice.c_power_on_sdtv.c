#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  aspect; } ;
typedef  TYPE_1__ SDTV_OPTIONS_T ;
typedef  int /*<<< orphan*/  SDTV_MODE_T ;
typedef  int /*<<< orphan*/  SDTV_ASPECT_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOG_STD (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDTV_MODE_PROGRESSIVE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int vc_tv_sdtv_power_on (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int power_on_sdtv( SDTV_MODE_T mode,
                              SDTV_ASPECT_T aspect, int sdtv_progressive )
{
   int ret;
   SDTV_OPTIONS_T options;
   memset(&options, 0, sizeof options);
   options.aspect = aspect;
   if (sdtv_progressive)
      mode |= SDTV_MODE_PROGRESSIVE;
   LOG_STD( "Powering on SDTV with explicit settings (mode:%d aspect:%d)",
            mode, aspect );

   ret = vc_tv_sdtv_power_on(mode, &options);
   if ( ret != 0 )
   {
      LOG_ERR( "Failed to power on SDTV with explicit settings (mode:%d aspect:%d)",
               mode, aspect );
   }

   return ret;
}