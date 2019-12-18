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
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  times ;
typedef  scalar_t__ time_t ;
struct tm {int tm_year; int tm_wday; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;
struct TYPE_8__ {scalar_t__ Status; } ;
struct TYPE_7__ {int resd; int regionid; int dotsel; int mshnmi; int sysres; int sndres; int cdres; int* SMEM; scalar_t__ basetime; scalar_t__ clocksync; } ;
struct TYPE_6__ {int* OREG; } ;
struct TYPE_5__ {int tm_year; int tm_wday; int tm_mday; int tm_mon; int tm_sec; int tm_min; int tm_hour; } ;

/* Variables and functions */
 TYPE_4__ Movie ; 
 scalar_t__ Playback ; 
 scalar_t__ Recording ; 
 TYPE_3__* SmpcInternalVars ; 
 TYPE_2__* SmpcRegs ; 
 int framecounter ; 
 int /*<<< orphan*/  internal_localtime_r (scalar_t__*,struct tm*) ; 
 int /*<<< orphan*/  localtime (scalar_t__*) ; 
 int /*<<< orphan*/  localtime_r (scalar_t__*,struct tm*) ; 
 int /*<<< orphan*/  memcpy (struct tm*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ movietime ; 
 int noon ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int totalseconds ; 

__attribute__((used)) static void SmpcINTBACKStatus(void) {
   // return time, cartidge, zone, etc. data
   int i;
   struct tm times;
   u8 year[4];
   time_t tmp;

   SmpcRegs->OREG[0] = 0x80 | (SmpcInternalVars->resd << 6);   // goto normal startup
   //SmpcRegs->OREG[0] = 0x0 | (SmpcInternalVars->resd << 6);  // goto setclock/setlanguage screen

   // write time data in OREG1-7
   if (SmpcInternalVars->clocksync) {
      tmp = SmpcInternalVars->basetime + ((u64)framecounter * 1001 / 60000);
   } else {
      tmp = time(NULL);
   }
#ifdef WIN32
   memcpy(&times, localtime(&tmp), sizeof(times));
#elif defined(__CELLOS_LV2__)
   memcpy(&times, localtime(&tmp), sizeof(times));
#elif defined(_arch_dreamcast) || defined(PSP) && !defined(__LIBRETRO__)
   internal_localtime_r(&tmp, &times);
#else
   localtime_r(&tmp, &times);
#endif
   year[0] = (1900 + times.tm_year) / 1000;
   year[1] = ((1900 + times.tm_year) % 1000) / 100;
   year[2] = (((1900 + times.tm_year) % 1000) % 100) / 10;
   year[3] = (((1900 + times.tm_year) % 1000) % 100) % 10;
   SmpcRegs->OREG[1] = (year[0] << 4) | year[1];
   SmpcRegs->OREG[2] = (year[2] << 4) | year[3];
   SmpcRegs->OREG[3] = (times.tm_wday << 4) | (times.tm_mon + 1);
   SmpcRegs->OREG[4] = ((times.tm_mday / 10) << 4) | (times.tm_mday % 10);
   SmpcRegs->OREG[5] = ((times.tm_hour / 10) << 4) | (times.tm_hour % 10);
   SmpcRegs->OREG[6] = ((times.tm_min / 10) << 4) | (times.tm_min % 10);
   SmpcRegs->OREG[7] = ((times.tm_sec / 10) << 4) | (times.tm_sec % 10);

   if(Movie.Status == Recording || Movie.Status == Playback) {
	   movietime.tm_year=0x62;
	   movietime.tm_wday=0x04;
	   movietime.tm_mday=0x01;
	   movietime.tm_mon=0;
	   totalseconds = ((framecounter / 60) + noon);

	   movietime.tm_sec=totalseconds % 60;
	   movietime.tm_min=totalseconds/60;
	   movietime.tm_hour=movietime.tm_min/60;

	   //convert to sane numbers
	   movietime.tm_min=movietime.tm_min % 60;
	   movietime.tm_hour=movietime.tm_hour % 24;

	   year[0] = (1900 + movietime.tm_year) / 1000;
	   year[1] = ((1900 + movietime.tm_year) % 1000) / 100;
	   year[2] = (((1900 + movietime.tm_year) % 1000) % 100) / 10;
	   year[3] = (((1900 + movietime.tm_year) % 1000) % 100) % 10;
	   SmpcRegs->OREG[1] = (year[0] << 4) | year[1];
	   SmpcRegs->OREG[2] = (year[2] << 4) | year[3];
	   SmpcRegs->OREG[3] = (movietime.tm_wday << 4) | (movietime.tm_mon + 1);
	   SmpcRegs->OREG[4] = ((movietime.tm_mday / 10) << 4) | (movietime.tm_mday % 10);
	   SmpcRegs->OREG[5] = ((movietime.tm_hour / 10) << 4) | (movietime.tm_hour % 10);
	   SmpcRegs->OREG[6] = ((movietime.tm_min / 10) << 4) | (movietime.tm_min % 10);
	   SmpcRegs->OREG[7] = ((movietime.tm_sec / 10) << 4) | (movietime.tm_sec % 10);
   }

   // write cartidge data in OREG8
   SmpcRegs->OREG[8] = 0; // FIXME : random value

   // write zone data in OREG9 bits 0-7
   // 1 -> japan
   // 2 -> asia/ntsc
   // 4 -> north america
   // 5 -> central/south america/ntsc
   // 6 -> corea
   // A -> asia/pal
   // C -> europe + others/pal
   // D -> central/south america/pal
   SmpcRegs->OREG[9] = SmpcInternalVars->regionid;

   // system state, first part in OREG10, bits 0-7
   // bit | value  | comment
   // ---------------------------
   // 7   | 0      |
   // 6   | DOTSEL |
   // 5   | 1      |
   // 4   | 1      |
   // 3   | MSHNMI |
   // 2   | 1      |
   // 1   | SYSRES |
   // 0   | SNDRES |
   SmpcRegs->OREG[10] = 0x34|(SmpcInternalVars->dotsel<<6)|(SmpcInternalVars->mshnmi<<3)|(SmpcInternalVars->sysres<<1)|SmpcInternalVars->sndres;

   // system state, second part in OREG11, bit 6
   // bit 6 -> CDRES
   SmpcRegs->OREG[11] = SmpcInternalVars->cdres << 6; // FIXME

   // SMEM
   for(i = 0;i < 4;i++)
      SmpcRegs->OREG[12+i] = SmpcInternalVars->SMEM[i];

   SmpcRegs->OREG[31] = 0x10; // set to intback command
}