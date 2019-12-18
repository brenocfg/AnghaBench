#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* name; int /*<<< orphan*/ * interface; void* mounted; } ;
struct TYPE_6__ {int fbWidth; int /*<<< orphan*/  xfbHeight; } ;
typedef  TYPE_1__ GXRModeObj ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_Init (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GDBSTUB_DEVICE_USB ; 
 size_t GX_DEVICE_SD ; 
 size_t GX_DEVICE_USB ; 
 int /*<<< orphan*/  IOS_GetVersion () ; 
 int /*<<< orphan*/  IOS_ReloadIOS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  L2Enhance () ; 
 void* MEM_K0_TO_K1 (int /*<<< orphan*/ ) ; 
 size_t STD_ERR ; 
 size_t STD_OUT ; 
 int /*<<< orphan*/  SYS_AllocateFramebuffer (TYPE_1__*) ; 
 int /*<<< orphan*/  VIConfigure (TYPE_1__*) ; 
 TYPE_1__* VIDEO_GetPreferredMode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VIFlush () ; 
 int /*<<< orphan*/  VIInit () ; 
 int /*<<< orphan*/  VISetBlack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VISetNextFramebuffer (void*) ; 
 int /*<<< orphan*/  VIWaitForRetrace () ; 
 int VI_DISPLAY_PIX_SZ ; 
 int /*<<< orphan*/  __exception_setreload (int) ; 
 int /*<<< orphan*/  __io_usbstorage ; 
 int /*<<< orphan*/  __io_wiisd ; 
 int /*<<< orphan*/  _break () ; 
 int /*<<< orphan*/  console_init (void*,int,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ ** devoptab_list ; 
 int /*<<< orphan*/  dotab_stdout ; 
 int /*<<< orphan*/  fatInitDefault () ; 
 void* fatMountSimple (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gx_device_cond ; 
 void* gx_device_cond_mutex ; 
 void* gx_device_mutex ; 
 int /*<<< orphan*/  gx_device_thread ; 
 TYPE_2__* gx_devices ; 
 int /*<<< orphan*/  gx_devthread ; 
 int /*<<< orphan*/  gx_init_mem2 () ; 
 int /*<<< orphan*/  scond_new () ; 
 void* slock_new () ; 
 int /*<<< orphan*/  sthread_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void frontend_gx_init(void *data)
{
   (void)data;
#ifdef HW_RVL
   IOS_ReloadIOS(IOS_GetVersion());
   L2Enhance();
#ifndef IS_SALAMANDER
   gx_init_mem2();
#endif
#endif

#ifdef USBGECKO
   DEBUG_Init(GDBSTUB_DEVICE_USB, 1);
   _break();
#endif

#if defined(DEBUG) && defined(IS_SALAMANDER)
   VIInit();
   GXRModeObj *rmode = VIDEO_GetPreferredMode(NULL);
   void *xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
   console_init(xfb, 20, 20, rmode->fbWidth,
         rmode->xfbHeight, rmode->fbWidth * VI_DISPLAY_PIX_SZ);
   VIConfigure(rmode);
   VISetNextFramebuffer(xfb);
   VISetBlack(FALSE);
   VIFlush();
   VIWaitForRetrace();
   VIWaitForRetrace();
#endif

#ifndef DEBUG
   __exception_setreload(8);
#endif

   fatInitDefault();

   devoptab_list[STD_OUT] = &dotab_stdout;
   devoptab_list[STD_ERR] = &dotab_stdout;

#if defined(HW_RVL) && !defined(IS_SALAMANDER)
   gx_devices[GX_DEVICE_SD].interface = &__io_wiisd;
   gx_devices[GX_DEVICE_SD].name = "sd";
   gx_devices[GX_DEVICE_SD].mounted = fatMountSimple(
         gx_devices[GX_DEVICE_SD].name,
         gx_devices[GX_DEVICE_SD].interface);
   gx_devices[GX_DEVICE_USB].interface = &__io_usbstorage;
   gx_devices[GX_DEVICE_USB].name = "usb";
   gx_devices[GX_DEVICE_USB].mounted = fatMountSimple(
            gx_devices[GX_DEVICE_USB].name,
            gx_devices[GX_DEVICE_USB].interface);

   gx_device_cond_mutex = slock_new();
   gx_device_cond       = scond_new();
   gx_device_mutex      = slock_new();
   gx_device_thread     = sthread_create(gx_devthread, NULL);
#endif
}