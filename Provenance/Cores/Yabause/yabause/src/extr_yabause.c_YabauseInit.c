#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int numthreads; scalar_t__ skip_load; int /*<<< orphan*/ * ssfpath; int /*<<< orphan*/  sndcoretype; int /*<<< orphan*/  m68kcoretype; scalar_t__ play_ssf; int /*<<< orphan*/ * biospath; int /*<<< orphan*/  osdcoretype; scalar_t__ frameskip; int /*<<< orphan*/  videoformattype; int /*<<< orphan*/  basetime; int /*<<< orphan*/  clocksync; int /*<<< orphan*/  regionid; int /*<<< orphan*/  modemport; int /*<<< orphan*/  modemip; int /*<<< orphan*/  mpegpath; int /*<<< orphan*/  cdpath; int /*<<< orphan*/  cdcoretype; int /*<<< orphan*/  carttype; int /*<<< orphan*/  percoretype; int /*<<< orphan*/  vidcoretype; int /*<<< orphan*/  cartpath; int /*<<< orphan*/  buppath; int /*<<< orphan*/  sh2coretype; scalar_t__ usethreads; } ;
typedef  TYPE_1__ yabauseinit_struct ;
struct TYPE_7__ {int id; } ;
struct TYPE_6__ {int NumThreads; int DecilineMode; int emulatebios; int playing_ssf; scalar_t__ UseThreads; scalar_t__ usequickload; } ;

/* Variables and functions */
 int /*<<< orphan*/ * BiosRom ; 
 int /*<<< orphan*/ * BupRam ; 
 scalar_t__ BupRamWritten ; 
 int /*<<< orphan*/  CLKTYPE_26MHZ ; 
 scalar_t__ CartInit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CheatInit () ; 
 scalar_t__ Cs2Init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnableAutoFrameSkip () ; 
 int /*<<< orphan*/  FormatBackupRam (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  GdbStubInit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * HighWram ; 
 scalar_t__ LoadBackupRam (int /*<<< orphan*/ ) ; 
 scalar_t__ LoadBios (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * LowWram ; 
 scalar_t__ M68KInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSH2 ; 
 int /*<<< orphan*/  MappedMemoryInit () ; 
 int /*<<< orphan*/  OSDCORE_DEFAULT ; 
 int /*<<< orphan*/  OSDChangeCore (int /*<<< orphan*/ ) ; 
 scalar_t__ PerInit (int /*<<< orphan*/ ) ; 
 TYPE_4__* SH2Core ; 
 scalar_t__ SH2Init (int /*<<< orphan*/ ) ; 
 scalar_t__ ScspInit (int /*<<< orphan*/ ) ; 
 scalar_t__ ScuInit () ; 
 scalar_t__ SmpcInit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * T1MemoryInit (int) ; 
 void* T2MemoryInit (int) ; 
 int /*<<< orphan*/  VIDSoftSetNumLayerThreads (int) ; 
 int /*<<< orphan*/  VIDSoftSetNumPriorityThreads (int) ; 
 int /*<<< orphan*/  VIDSoftSetVdp1ThreadEnable (int) ; 
 scalar_t__ Vdp1Init () ; 
 scalar_t__ Vdp2Init () ; 
 scalar_t__ VideoInit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YAB_ERR_CANNOTINIT ; 
 int /*<<< orphan*/  YAB_ERR_FILENOTFOUND ; 
 int /*<<< orphan*/  YabSetError (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  YabauseChangeTiming (int /*<<< orphan*/ ) ; 
 scalar_t__ YabauseQuickLoadGame () ; 
 int /*<<< orphan*/  YabauseResetNoLoad () ; 
 int /*<<< orphan*/  YabauseSetVideoFormat (int /*<<< orphan*/ ) ; 
 void* _ (char*) ; 
 int /*<<< orphan*/  bupfilename ; 
 int /*<<< orphan*/  get_ssf_info (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_ssf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh2_dynarec_init () ; 
 int /*<<< orphan*/  ssf_artist ; 
 int /*<<< orphan*/  ssf_track_name ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 
 TYPE_2__ yabsys ; 

int YabauseInit(yabauseinit_struct *init)
{
   // Need to set this first, so init routines see it
   yabsys.UseThreads = init->usethreads;
   yabsys.NumThreads = init->numthreads;

   // Initialize both cpu's
   if (SH2Init(init->sh2coretype) != 0)
   {
      YabSetError(YAB_ERR_CANNOTINIT, _("SH2"));
      return -1;
   }

   if ((BiosRom = T2MemoryInit(0x80000)) == NULL)
      return -1;

   if ((HighWram = T2MemoryInit(0x100000)) == NULL)
      return -1;

   if ((LowWram = T2MemoryInit(0x100000)) == NULL)
      return -1;

   if ((BupRam = T1MemoryInit(0x10000)) == NULL)
      return -1;

   if (LoadBackupRam(init->buppath) != 0)
      FormatBackupRam(BupRam, 0x10000);

   BupRamWritten = 0;

   bupfilename = init->buppath;

   if (CartInit(init->cartpath, init->carttype) != 0)
   {
      YabSetError(YAB_ERR_CANNOTINIT, _("Cartridge"));
      return -1;
   }

   MappedMemoryInit();

   if (VideoInit(init->vidcoretype) != 0)
   {
      YabSetError(YAB_ERR_CANNOTINIT, _("Video"));
      return -1;
   }

   // Initialize input core
   if (PerInit(init->percoretype) != 0)
   {
      YabSetError(YAB_ERR_CANNOTINIT, _("Peripheral"));
      return -1;
   }

   if (Cs2Init(init->carttype, init->cdcoretype, init->cdpath, init->mpegpath, init->modemip, init->modemport) != 0)
   {
      YabSetError(YAB_ERR_CANNOTINIT, _("CS2"));
      return -1;
   }

   if (ScuInit() != 0)
   {
      YabSetError(YAB_ERR_CANNOTINIT, _("SCU"));
      return -1;
   }

   if (M68KInit(init->m68kcoretype) != 0)
   {
      YabSetError(YAB_ERR_CANNOTINIT, _("M68K"));
      return -1;
   }

   if (ScspInit(init->sndcoretype) != 0)
   {
      YabSetError(YAB_ERR_CANNOTINIT, _("SCSP/M68K"));
      return -1;
   }

   if (Vdp1Init() != 0)
   {
      YabSetError(YAB_ERR_CANNOTINIT, _("VDP1"));
      return -1;
   }

   if (Vdp2Init() != 0)
   {
      YabSetError(YAB_ERR_CANNOTINIT, _("VDP2"));
      return -1;
   }

   if (SmpcInit(init->regionid, init->clocksync, init->basetime) != 0)
   {
      YabSetError(YAB_ERR_CANNOTINIT, _("SMPC"));
      return -1;
   }

   if (CheatInit() != 0)
   {
      YabSetError(YAB_ERR_CANNOTINIT, _("Cheat System"));
      return -1;
   }

   YabauseSetVideoFormat(init->videoformattype);
   YabauseChangeTiming(CLKTYPE_26MHZ);
   yabsys.DecilineMode = 1;

   if (init->frameskip)
      EnableAutoFrameSkip();

#ifdef YAB_PORT_OSD
   OSDChangeCore(init->osdcoretype);
#else
   OSDChangeCore(OSDCORE_DEFAULT);
#endif

   if (init->biospath != NULL && strlen(init->biospath))
   {
      if (LoadBios(init->biospath) != 0)
      {
         YabSetError(YAB_ERR_FILENOTFOUND, (void *)init->biospath);
         return -2;
      }
      yabsys.emulatebios = 0;
   }
   else
      yabsys.emulatebios = 1;

   yabsys.usequickload = 0;

   #if defined(SH2_DYNAREC)
   if(SH2Core->id==2) {
     sh2_dynarec_init();
   }
   #endif

   YabauseResetNoLoad();

#ifdef YAB_WANT_SSF

   if (init->play_ssf && init->ssfpath != NULL && strlen(init->ssfpath))
   {
      if (!load_ssf((char*)init->ssfpath, init->m68kcoretype, init->sndcoretype))
      {
         YabSetError(YAB_ERR_FILENOTFOUND, (void *)init->ssfpath);

         yabsys.playing_ssf = 0;

         return -2;
      }

      yabsys.playing_ssf = 1;

      get_ssf_info(1, ssf_track_name);
      get_ssf_info(3, ssf_artist);

      return 0;
   }
   else
      yabsys.playing_ssf = 0;

#endif

   if (init->skip_load)
   {
	   return 0;
   }

   if (yabsys.usequickload || yabsys.emulatebios)
   {
      if (YabauseQuickLoadGame() != 0)
      {
         if (yabsys.emulatebios)
         {
            YabSetError(YAB_ERR_CANNOTINIT, _("Game"));
            return -2;
         }
         else
            YabauseResetNoLoad();
      }
   }

#ifdef HAVE_GDBSTUB
   GdbStubInit(MSH2, 43434);
#endif

   if (yabsys.UseThreads)
   {
      int num = yabsys.NumThreads < 1 ? 1 : yabsys.NumThreads;
      VIDSoftSetVdp1ThreadEnable(num == 1 ? 0 : 1);
      VIDSoftSetNumLayerThreads(num);
      VIDSoftSetNumPriorityThreads(num);
   }
   else
   {
      VIDSoftSetVdp1ThreadEnable(0);
      VIDSoftSetNumLayerThreads(0);
      VIDSoftSetNumPriorityThreads(0);
   }

   return 0;
}