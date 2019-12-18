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
typedef  int /*<<< orphan*/  cwd ;

/* Variables and functions */
 int CDVD_Init () ; 
 int FILENAME_MAX ; 
 int /*<<< orphan*/  MC_TYPE_XMC ; 
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 int /*<<< orphan*/  SCECdINoD ; 
 int /*<<< orphan*/  SifExecModuleBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SifInitRpc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SifIopReset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SifIopSync () ; 
 int /*<<< orphan*/  _init_ps2_io () ; 
 scalar_t__ audsrv_init () ; 
 int /*<<< orphan*/  audsrv_irx ; 
 int /*<<< orphan*/  cdvd_irx ; 
 int /*<<< orphan*/  fileXio_irx ; 
 int /*<<< orphan*/  freemtap_irx ; 
 int /*<<< orphan*/  freepad_irx ; 
 int /*<<< orphan*/  freesd_irx ; 
 int /*<<< orphan*/  freesio2_irx ; 
 int getBootDeviceID (char*) ; 
 int /*<<< orphan*/  getcwd (char*,int) ; 
 int /*<<< orphan*/  iomanX_irx ; 
 scalar_t__ mcInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcman_irx ; 
 int /*<<< orphan*/  mcserv_irx ; 
 int mtapInit () ; 
 int mtapPortOpen (int /*<<< orphan*/ ) ; 
 int padInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  retro_main_log_file_init (char*,int) ; 
 int /*<<< orphan*/  sbv_patch_enable_lmb () ; 
 int /*<<< orphan*/  sceCdInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_audsrv_irx ; 
 int /*<<< orphan*/  size_cdvd_irx ; 
 int /*<<< orphan*/  size_fileXio_irx ; 
 int /*<<< orphan*/  size_freemtap_irx ; 
 int /*<<< orphan*/  size_freepad_irx ; 
 int /*<<< orphan*/  size_freesd_irx ; 
 int /*<<< orphan*/  size_freesio2_irx ; 
 int /*<<< orphan*/  size_iomanX_irx ; 
 int /*<<< orphan*/  size_mcman_irx ; 
 int /*<<< orphan*/  size_mcserv_irx ; 
 int /*<<< orphan*/  size_usbd_irx ; 
 int /*<<< orphan*/  size_usbhdfsd_irx ; 
 int /*<<< orphan*/  usbd_irx ; 
 int /*<<< orphan*/  usbhdfsd_irx ; 
 int /*<<< orphan*/  verbosity_enable () ; 
 int /*<<< orphan*/  waitUntilDeviceIsReady (int) ; 

__attribute__((used)) static void frontend_ps2_init(void *data)
{
   char cwd[FILENAME_MAX];
   int bootDeviceID;

   SifInitRpc(0);
#if !defined(DEBUG) || defined(BUILD_FOR_PCSX2)
   /* Comment this line if you don't wanna debug the output */
   while(!SifIopReset(NULL, 0)){};
#endif

   while(!SifIopSync()){};
   SifInitRpc(0);
   sbv_patch_enable_lmb();

   /* I/O Files */
   SifExecModuleBuffer(&iomanX_irx, size_iomanX_irx, 0, NULL, NULL);
   SifExecModuleBuffer(&fileXio_irx, size_fileXio_irx, 0, NULL, NULL);
   SifExecModuleBuffer(&freesio2_irx, size_freesio2_irx, 0, NULL, NULL);

   /* Memory Card */
   SifExecModuleBuffer(&mcman_irx, size_mcman_irx, 0, NULL, NULL);
   SifExecModuleBuffer(&mcserv_irx, size_mcserv_irx, 0, NULL, NULL);

   /* Controllers */
   SifExecModuleBuffer(&freemtap_irx, size_freemtap_irx, 0, NULL, NULL);
   SifExecModuleBuffer(&freepad_irx, size_freepad_irx, 0, NULL, NULL);

   /* USB */
   SifExecModuleBuffer(&usbd_irx, size_usbd_irx, 0, NULL, NULL);
   SifExecModuleBuffer(&usbhdfsd_irx, size_usbhdfsd_irx, 0, NULL, NULL);

   /* Audio */
   SifExecModuleBuffer(&freesd_irx, size_freesd_irx, 0, NULL, NULL);
   SifExecModuleBuffer(&audsrv_irx, size_audsrv_irx, 0, NULL, NULL);

   /* CDVD */
   SifExecModuleBuffer(&cdvd_irx, size_cdvd_irx, 0, NULL, NULL);

   if (mcInit(MC_TYPE_XMC)) {
      RARCH_ERR("mcInit library not initalizated\n");
   }

   /* Initializes audsrv library */
   if (audsrv_init()) {
      RARCH_ERR("audsrv library not initalizated\n");
   }

   /* Initializes pad libraries
      Must be init with 0 as parameter*/
   if (mtapInit() != 1) {
      RARCH_ERR("mtapInit library not initalizated\n");
   }
   if (padInit(0) != 1) {
      RARCH_ERR("padInit library not initalizated\n");
   }
   if (mtapPortOpen(0) != 1) {
      RARCH_ERR("mtapPortOpen library not initalizated\n");
   }

   /* Initializes CDVD library */
   /* SCECdINoD init without check for a disc. Reduces risk of a lockup if the drive is in a erroneous state. */
   sceCdInit(SCECdINoD);
   if (CDVD_Init() != 1) {
      RARCH_ERR("CDVD_Init library not initalizated\n");
   }

   _init_ps2_io();

   /* Prepare device */
   getcwd(cwd, sizeof(cwd));
   bootDeviceID=getBootDeviceID(cwd);
   waitUntilDeviceIsReady(bootDeviceID);

#if defined(HAVE_FILE_LOGGER)
   retro_main_log_file_init("retroarch.log", false);
   verbosity_enable();
#endif
}