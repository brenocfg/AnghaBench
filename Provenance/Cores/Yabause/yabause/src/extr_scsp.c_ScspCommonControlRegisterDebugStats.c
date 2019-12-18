#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ mcieb; scalar_t__ mcipd; scalar_t__ scilv2; scalar_t__ scilv1; scalar_t__ scilv0; scalar_t__ scieb; scalar_t__ scipd; scalar_t__ timcsd; scalar_t__ timccnt; scalar_t__ timbsd; scalar_t__ timbcnt; scalar_t__ timasd; scalar_t__ timacnt; scalar_t__ dmlen; scalar_t__ drga; scalar_t__ dmea; scalar_t__ ca; scalar_t__ mslc; scalar_t__ rbp; scalar_t__ rbl; scalar_t__ mvol; scalar_t__ mem4b; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddString (char*,char*,...) ; 
 scalar_t__ pow (int,double) ; 
 TYPE_1__ scsp ; 

void
ScspCommonControlRegisterDebugStats (char *outstring)
{
   AddString (outstring, "Memory: %s\r\n", scsp.mem4b ? "4 Mbit" : "2 Mbit");
   AddString (outstring, "Master volume: %ld\r\n", (unsigned long)scsp.mvol);
   AddString (outstring, "Ring buffer length: %ld\r\n", (unsigned long)scsp.rbl);
   AddString (outstring, "Ring buffer address: %08lX\r\n", (unsigned long)scsp.rbp);
   AddString (outstring, "\r\n");

   AddString (outstring, "Slot Status Registers\r\n");
   AddString (outstring, "-----------------\r\n");
   AddString (outstring, "Monitor slot: %ld\r\n", (unsigned long)scsp.mslc);
   AddString (outstring, "Call address: %ld\r\n", (unsigned long)scsp.ca);
   AddString (outstring, "\r\n");

   AddString (outstring, "DMA Registers\r\n");
   AddString (outstring, "-----------------\r\n");
   AddString (outstring, "DMA memory address start: %08lX\r\n", (unsigned long)scsp.dmea);
   AddString (outstring, "DMA register address start: %08lX\r\n", (unsigned long)scsp.drga);
   AddString (outstring, "DMA Flags: %lX\r\n", (unsigned long)scsp.dmlen);
   AddString (outstring, "\r\n");

   AddString (outstring, "Timer Registers\r\n");
   AddString (outstring, "-----------------\r\n");
   AddString (outstring, "Timer A counter: %02lX\r\n", (unsigned long)scsp.timacnt >> 8);
   AddString (outstring, "Timer A increment: Every %d sample(s)\r\n", (int)pow(2, (double)scsp.timasd));
   AddString (outstring, "Timer B counter: %02lX\r\n", (unsigned long)scsp.timbcnt >> 8);
   AddString (outstring, "Timer B increment: Every %d sample(s)\r\n", (int)pow(2, (double)scsp.timbsd));
   AddString (outstring, "Timer C counter: %02lX\r\n", (unsigned long)scsp.timccnt >> 8);
   AddString (outstring, "Timer C increment: Every %d sample(s)\r\n", (int)pow(2, (double)scsp.timcsd));
   AddString (outstring, "\r\n");

   AddString (outstring, "Interrupt Registers\r\n");
   AddString (outstring, "-----------------\r\n");
   AddString (outstring, "Sound cpu interrupt pending: %04lX\r\n", (unsigned long)scsp.scipd);
   AddString (outstring, "Sound cpu interrupt enable: %04lX\r\n", (unsigned long)scsp.scieb);
   AddString (outstring, "Sound cpu interrupt level 0: %04lX\r\n", (unsigned long)scsp.scilv0);
   AddString (outstring, "Sound cpu interrupt level 1: %04lX\r\n", (unsigned long)scsp.scilv1);
   AddString (outstring, "Sound cpu interrupt level 2: %04lX\r\n", (unsigned long)scsp.scilv2);
   AddString (outstring, "Main cpu interrupt pending: %04lX\r\n", (unsigned long)scsp.mcipd);
   AddString (outstring, "Main cpu interrupt enable: %04lX\r\n", (unsigned long)scsp.mcieb);
   AddString (outstring, "\r\n");
}