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
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  outputwidth ;
typedef  int /*<<< orphan*/  outputheight ;
struct TYPE_7__ {scalar_t__ id; int /*<<< orphan*/  (* GetGlSize ) (int*,int*) ;} ;
struct TYPE_6__ {int UsecFrac; int /*<<< orphan*/  CurSH2FreqType; int /*<<< orphan*/  IsPal; int /*<<< orphan*/  MaxLineCount; int /*<<< orphan*/  VBlankLineCount; int /*<<< orphan*/  LineCount; int /*<<< orphan*/  DecilineCount; } ;
struct TYPE_5__ {int /*<<< orphan*/  size; scalar_t__ done; } ;
typedef  TYPE_1__ IOCheck_struct ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ BupRam ; 
 int /*<<< orphan*/  CartLoadState (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  Cs2LoadState (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  GL_RGBA ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 scalar_t__ HighWram ; 
 scalar_t__ LowWram ; 
 int /*<<< orphan*/  MSH2 ; 
 int /*<<< orphan*/  MovieReadState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OSDMSG_STATUS ; 
 int /*<<< orphan*/  OSDPushMessage (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  SCSP_MUTE_SYSTEM ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SH2LoadState (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  SSH2 ; 
 int /*<<< orphan*/  ScspMuteAudio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScspUnMuteAudio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScuLoadState (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  SmpcLoadState (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  SoundLoadState (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ StateCheckRetrieveHeader (int /*<<< orphan*/ *,char*,int*,int*) ; 
 scalar_t__ VIDCORE_OGL ; 
 scalar_t__ VIDCORE_SOFT ; 
 TYPE_4__* VIDCore ; 
 int /*<<< orphan*/  Vdp1LoadState (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  Vdp2LoadState (int /*<<< orphan*/ *,int,int) ; 
 int YABSYS_TIMING_BITS ; 
 int /*<<< orphan*/  YAB_ERR_OTHER ; 
 int /*<<< orphan*/  YabSetError (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  YabauseChangeTiming (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  YuiSwapBuffers () ; 
 int /*<<< orphan*/  framecounter ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glDrawPixels (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  glPixelZoom (float,float) ; 
 int /*<<< orphan*/  glRasterPos2i (int /*<<< orphan*/ ,int) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  stub1 (int*,int*) ; 
 TYPE_3__ yabsys ; 
 int /*<<< orphan*/  yread (TYPE_1__*,void*,int,int,int /*<<< orphan*/ *) ; 

int YabLoadStateStream(FILE *fp)
{
   char id[3];
   u8 endian;
   int headerversion, version, size, chunksize, headersize;
   IOCheck_struct check;
   u8* buf;
   int totalsize;
   int outputwidth;
   int outputheight;
   int curroutputwidth;
   int curroutputheight;
   int movieposition;
   int temp;
   u32 temp32;
   int test_endian;

   headersize = 0xC;
   check.done = 0;
   check.size = 0;

   // Read signature
   yread(&check, (void *)id, 1, 3, fp);

   if (strncmp(id, "YSS", 3) != 0)
   {
      return -2;
   }

   // Read header
   yread(&check, (void *)&endian, 1, 1, fp);
   yread(&check, (void *)&headerversion, 4, 1, fp);
   yread(&check, (void *)&size, 4, 1, fp);
   switch(headerversion)
   {
      case 1:
         /* This is the "original" version of the format */
         break;
      case 2:
         /* version 2 adds video recording */
         yread(&check, (void *)&framecounter, 4, 1, fp);
		 movieposition=ftell(fp);
		 yread(&check, (void *)&movieposition, 4, 1, fp);
         headersize = 0x14;
         break;
      default:
         /* we're trying to open a save state using a future version
          * of the YSS format, that won't work, sorry :) */
         return -3;
         break;
   }

#ifdef WORDS_BIGENDIAN
   test_endian = endian == 1;
#else
   test_endian = endian == 0;
#endif
   if (test_endian)
   {
      // should setup reading so it's byte-swapped
      YabSetError(YAB_ERR_OTHER, (void *)"Load State byteswapping not supported");
      return -3;
   }

   // Make sure size variable matches actual size minus header
   fseek(fp, 0, SEEK_END);

   if (size != (ftell(fp) - headersize))
   {
      return -2;
   }
   fseek(fp, headersize, SEEK_SET);

   // Verify version here

   ScspMuteAudio(SCSP_MUTE_SYSTEM);

   if (StateCheckRetrieveHeader(fp, "CART", &version, &chunksize) != 0)
   {
      // Revert back to old state here
      ScspUnMuteAudio(SCSP_MUTE_SYSTEM);
      return -3;
   }
   CartLoadState(fp, version, chunksize);

   if (StateCheckRetrieveHeader(fp, "CS2 ", &version, &chunksize) != 0)
   {
      // Revert back to old state here
      ScspUnMuteAudio(SCSP_MUTE_SYSTEM);
      return -3;
   }
   Cs2LoadState(fp, version, chunksize);

   if (StateCheckRetrieveHeader(fp, "MSH2", &version, &chunksize) != 0)
   {
      // Revert back to old state here
      ScspUnMuteAudio(SCSP_MUTE_SYSTEM);
      return -3;
   }
   SH2LoadState(MSH2, fp, version, chunksize);

   if (StateCheckRetrieveHeader(fp, "SSH2", &version, &chunksize) != 0)
   {
      // Revert back to old state here
      ScspUnMuteAudio(SCSP_MUTE_SYSTEM);
      return -3;
   }
   SH2LoadState(SSH2, fp, version, chunksize);

   if (StateCheckRetrieveHeader(fp, "SCSP", &version, &chunksize) != 0)
   {
      // Revert back to old state here
      ScspUnMuteAudio(SCSP_MUTE_SYSTEM);
      return -3;
   }
   SoundLoadState(fp, version, chunksize);

   if (StateCheckRetrieveHeader(fp, "SCU ", &version, &chunksize) != 0)
   {
      // Revert back to old state here
      ScspUnMuteAudio(SCSP_MUTE_SYSTEM);
      return -3;
   }
   ScuLoadState(fp, version, chunksize);

   if (StateCheckRetrieveHeader(fp, "SMPC", &version, &chunksize) != 0)
   {
      // Revert back to old state here
      ScspUnMuteAudio(SCSP_MUTE_SYSTEM);
      return -3;
   }
   SmpcLoadState(fp, version, chunksize);

   if (StateCheckRetrieveHeader(fp, "VDP1", &version, &chunksize) != 0)
   {
      // Revert back to old state here
      ScspUnMuteAudio(SCSP_MUTE_SYSTEM);
      return -3;
   }
   Vdp1LoadState(fp, version, chunksize);

   if (StateCheckRetrieveHeader(fp, "VDP2", &version, &chunksize) != 0)
   {
      // Revert back to old state here
      ScspUnMuteAudio(SCSP_MUTE_SYSTEM);
      return -3;
   }
   Vdp2LoadState(fp, version, chunksize);

   if (StateCheckRetrieveHeader(fp, "OTHR", &version, &chunksize) != 0)
   {
      // Revert back to old state here
      ScspUnMuteAudio(SCSP_MUTE_SYSTEM);
      return -3;
   }
   // Other data
   yread(&check, (void *)BupRam, 0x10000, 1, fp);
   yread(&check, (void *)HighWram, 0x100000, 1, fp);
   yread(&check, (void *)LowWram, 0x100000, 1, fp);

   yread(&check, (void *)&yabsys.DecilineCount, sizeof(int), 1, fp);
   yread(&check, (void *)&yabsys.LineCount, sizeof(int), 1, fp);
   yread(&check, (void *)&yabsys.VBlankLineCount, sizeof(int), 1, fp);
   yread(&check, (void *)&yabsys.MaxLineCount, sizeof(int), 1, fp);
   yread(&check, (void *)&temp, sizeof(int), 1, fp);
   yread(&check, (void *)&temp, sizeof(int), 1, fp);
   yread(&check, (void *)&temp32, sizeof(u32), 1, fp);
   yread(&check, (void *)&yabsys.CurSH2FreqType, sizeof(int), 1, fp);
   yread(&check, (void *)&yabsys.IsPal, sizeof(int), 1, fp);
   YabauseChangeTiming(yabsys.CurSH2FreqType);
   yabsys.UsecFrac = (temp32 << YABSYS_TIMING_BITS) * temp / 10;

   if (headerversion > 1) {

   yread(&check, (void *)&outputwidth, sizeof(outputwidth), 1, fp);
   yread(&check, (void *)&outputheight, sizeof(outputheight), 1, fp);

   totalsize=outputwidth * outputheight * sizeof(u32);

   if ((buf = (u8 *)malloc(totalsize)) == NULL)
   {
      return -2;
   }

   yread(&check, (void *)buf, totalsize, 1, fp);

   YuiSwapBuffers();

   #if defined(USE_OPENGL) && !defined(_OGLES3_)
   if(VIDCore->id == VIDCORE_SOFT)
     glRasterPos2i(0, outputheight);
   if(VIDCore->id == VIDCORE_OGL)
	 glRasterPos2i(0, outputheight/2);
   #endif

   VIDCore->GetGlSize(&curroutputwidth, &curroutputheight);
   #if defined(USE_OPENGL) && !defined(_OGLES3_)
   glPixelZoom((float)curroutputwidth / (float)outputwidth, ((float)curroutputheight / (float)outputheight));
   glDrawPixels(outputwidth, outputheight, GL_RGBA, GL_UNSIGNED_BYTE, buf);
   #endif
   YuiSwapBuffers();
   free(buf);

   fseek(fp, movieposition, SEEK_SET);
   MovieReadState(fp);
   }

   ScspUnMuteAudio(SCSP_MUTE_SYSTEM);

   OSDPushMessage(OSDMSG_STATUS, 150, "STATE LOADED");

   return 0;
}