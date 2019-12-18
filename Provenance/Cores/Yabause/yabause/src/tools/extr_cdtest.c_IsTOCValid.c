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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */

int IsTOCValid(u32 *TOC)
{
   u8 lasttrack=1;
   int i;

   // Make sure first track's FAD is 150
   if ((TOC[0] & 0xFFFFFF) != 150)
      return 0;

   // Go through each track and make sure they start at FAD that's higher
   // than the previous track
   for (i = 1; i < 99; i++)
   {
      if (TOC[i] == 0xFFFFFFFF)
         break;

      lasttrack++;

      if ((TOC[i-1] & 0xFFFFFF) >= (TOC[i] & 0xFFFFFF))
         return 0;
   }

   // Check Point A0 information
   if (TOC[99] & 0xFF) // PFRAME - Should always be 0
      return 0;

   if (TOC[99] & 0xFF00) // PSEC - Saturn discs will be 0
      return 0;

   if (((TOC[99] & 0xFF0000) >> 16) != 0x01) // PMIN - First track's number
      return 0;

   if ((TOC[99] & 0xFF000000) != (TOC[0] & 0xFF000000)) // First track's addr/ctrl
      return 0;

   // Check Point A1 information
   if (TOC[100] & 0xFF) // PFRAME - Should always be 0
      return 0;

   if (TOC[100] & 0xFF00) // PSEC - Saturn discs will be 0
      return 0;

   if (((TOC[100] & 0xFF0000) >> 16) != lasttrack) // PMIN - Last track's number
      return 0;

   if ((TOC[100] & 0xFF000000) != (TOC[lasttrack-1] & 0xFF000000)) // Last track's addr/ctrl
      return 0;

   // Check Point A2 information
   if ((TOC[101] & 0xFFFFFF) <= (TOC[lasttrack-1] & 0xFFFFFF)) // Lead out FAD should be larger than last track's FAD
      return 0;

   if ((TOC[101] & 0xFF000000) != (TOC[lasttrack-1] & 0xFF000000)) // Lead out's addr/ctrl should be the same as last track's
      return 0;

   return 1;
}