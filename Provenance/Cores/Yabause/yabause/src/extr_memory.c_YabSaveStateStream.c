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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  outputwidth ;
typedef  int /*<<< orphan*/  outputheight ;
typedef  int /*<<< orphan*/  movieposition ;
typedef  int /*<<< orphan*/  i ;
struct TYPE_8__ {int /*<<< orphan*/  (* GetGlSize ) (int*,int*) ;} ;
struct TYPE_7__ {int DecilineStop; scalar_t__ CurSH2FreqType; int UsecFrac; int /*<<< orphan*/  IsPal; int /*<<< orphan*/  MaxLineCount; int /*<<< orphan*/  VBlankLineCount; int /*<<< orphan*/  LineCount; int /*<<< orphan*/  DecilineCount; } ;
struct TYPE_6__ {scalar_t__ size; scalar_t__ done; } ;
typedef  TYPE_1__ IOCheck_struct ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ BupRam ; 
 scalar_t__ CLKTYPE_26MHZ ; 
 scalar_t__ CartSaveState (int /*<<< orphan*/ *) ; 
 scalar_t__ Cs2SaveState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GL_BACK ; 
 int /*<<< orphan*/  GL_RGBA ; 
 int /*<<< orphan*/  GL_UNSIGNED_BYTE ; 
 scalar_t__ HighWram ; 
 scalar_t__ LowWram ; 
 int /*<<< orphan*/  MSH2 ; 
 int /*<<< orphan*/  OSDMSG_STATUS ; 
 int /*<<< orphan*/  OSDPushMessage (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ SH2SaveState (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSH2 ; 
 int /*<<< orphan*/  SaveMovieInState (int /*<<< orphan*/ *,TYPE_1__) ; 
 scalar_t__ ScuSaveState (int /*<<< orphan*/ *) ; 
 scalar_t__ SmpcSaveState (int /*<<< orphan*/ *) ; 
 scalar_t__ SoundSaveState (int /*<<< orphan*/ *) ; 
 scalar_t__ StateFinishHeader (int /*<<< orphan*/ *,int) ; 
 int StateWriteHeader (int /*<<< orphan*/ *,char*,int) ; 
 TYPE_4__* VIDCore ; 
 scalar_t__ Vdp1SaveState (int /*<<< orphan*/ *) ; 
 scalar_t__ Vdp2SaveState (int /*<<< orphan*/ *) ; 
 int YABSYS_TIMING_BITS ; 
 int /*<<< orphan*/  YuiSwapBuffers () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fputc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  framecounter ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glPixelZoom (int,int) ; 
 int /*<<< orphan*/  glReadBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glReadPixels (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  stub1 (int*,int*) ; 
 TYPE_3__ yabsys ; 
 int /*<<< orphan*/  ywrite (TYPE_1__*,void*,int,int,int /*<<< orphan*/ *) ; 

int YabSaveStateStream(FILE *fp)
{
   u32 i;
   int offset;
   IOCheck_struct check;
   u8 *buf;
   int totalsize;
   int outputwidth;
   int outputheight;
   int movieposition;
   int temp;
   u32 temp32;

   check.done = 0;
   check.size = 0;

   // Write signature
   fprintf(fp, "YSS");

   // Write endianness byte
#ifdef WORDS_BIGENDIAN
   fputc(0x00, fp);
#else
   fputc(0x01, fp);
#endif

   // Write version(fix me)
   i = 2;
   ywrite(&check, (void *)&i, sizeof(i), 1, fp);

   // Skip the next 4 bytes for now
   i = 0;
   ywrite(&check, (void *)&i, sizeof(i), 1, fp);

   //write frame number
   ywrite(&check, (void *)&framecounter, 4, 1, fp);

   //this will be updated with the movie position later
   ywrite(&check, (void *)&framecounter, 4, 1, fp);

   // Go through each area and write each state
   i += CartSaveState(fp);
   i += Cs2SaveState(fp);
   i += SH2SaveState(MSH2, fp);
   i += SH2SaveState(SSH2, fp);
   i += SoundSaveState(fp);
   i += ScuSaveState(fp);
   i += SmpcSaveState(fp);
   i += Vdp1SaveState(fp);
   i += Vdp2SaveState(fp);

   offset = StateWriteHeader(fp, "OTHR", 1);

   // Other data
   ywrite(&check, (void *)BupRam, 0x10000, 1, fp); // do we really want to save this?
   ywrite(&check, (void *)HighWram, 0x100000, 1, fp);
   ywrite(&check, (void *)LowWram, 0x100000, 1, fp);

   ywrite(&check, (void *)&yabsys.DecilineCount, sizeof(int), 1, fp);
   ywrite(&check, (void *)&yabsys.LineCount, sizeof(int), 1, fp);
   ywrite(&check, (void *)&yabsys.VBlankLineCount, sizeof(int), 1, fp);
   ywrite(&check, (void *)&yabsys.MaxLineCount, sizeof(int), 1, fp);
   temp = yabsys.DecilineStop >> YABSYS_TIMING_BITS;
   ywrite(&check, (void *)&temp, sizeof(int), 1, fp);
   temp = (yabsys.CurSH2FreqType == CLKTYPE_26MHZ) ? 268 : 286;
   ywrite(&check, (void *)&temp, sizeof(int), 1, fp);
   temp32 = (yabsys.UsecFrac * temp / 10) >> YABSYS_TIMING_BITS;
   ywrite(&check, (void *)&temp32, sizeof(u32), 1, fp);
   ywrite(&check, (void *)&yabsys.CurSH2FreqType, sizeof(int), 1, fp);
   ywrite(&check, (void *)&yabsys.IsPal, sizeof(int), 1, fp);

   VIDCore->GetGlSize(&outputwidth, &outputheight);

   totalsize=outputwidth * outputheight * sizeof(u32);

   if ((buf = (u8 *)malloc(totalsize)) == NULL)
   {
      return -2;
   }

   YuiSwapBuffers();
   #if defined(USE_OPENGL) && !defined(_OGLES3_)
   glPixelZoom(1,1);
   glReadBuffer(GL_BACK);
   glReadPixels(0, 0, outputwidth, outputheight, GL_RGBA, GL_UNSIGNED_BYTE, buf);
   #endif
   YuiSwapBuffers();

   ywrite(&check, (void *)&outputwidth, sizeof(outputwidth), 1, fp);
   ywrite(&check, (void *)&outputheight, sizeof(outputheight), 1, fp);

   ywrite(&check, (void *)buf, totalsize, 1, fp);

   movieposition=ftell(fp);
   //write the movie to the end of the savestate
   SaveMovieInState(fp, check);

   i += StateFinishHeader(fp, offset);

   // Go back and update size
   fseek(fp, 8, SEEK_SET);
   ywrite(&check, (void *)&i, sizeof(i), 1, fp);
   fseek(fp, 16, SEEK_SET);
   ywrite(&check, (void *)&movieposition, sizeof(movieposition), 1, fp);

   free(buf);

   OSDPushMessage(OSDMSG_STATUS, 150, "STATE SAVED");

   return 0;
}