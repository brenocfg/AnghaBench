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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct filter_data {int* tbl_5_to_8; int* tbl_6_to_8; int* RGBtoYUV; } ;

/* Variables and functions */
 int BLUE_MASK565 ; 
 int GREEN_MASK565 ; 
 int RED_MASK565 ; 

__attribute__((used)) static void SetupFormat(void * data)
{
   uint32_t c;
   struct filter_data *filt = (struct filter_data*)data;

   filt->tbl_5_to_8[0]  = 0;
   filt->tbl_5_to_8[1]  = 8;
   filt->tbl_5_to_8[2]  = 16;
   filt->tbl_5_to_8[3]  = 25;
   filt->tbl_5_to_8[4]  = 33;
   filt->tbl_5_to_8[5]  = 41;
   filt->tbl_5_to_8[6]  = 49;
   filt->tbl_5_to_8[7]  = 58;
   filt->tbl_5_to_8[8]  = 66;
   filt->tbl_5_to_8[9]  = 74;
   filt->tbl_5_to_8[10] = 82;
   filt->tbl_5_to_8[11] = 90;
   filt->tbl_5_to_8[12] = 99;
   filt->tbl_5_to_8[13] = 107;
   filt->tbl_5_to_8[14] = 115;
   filt->tbl_5_to_8[15] = 123;
   filt->tbl_5_to_8[16] = 132;
   filt->tbl_5_to_8[17] = 140;
   filt->tbl_5_to_8[18] = 148;
   filt->tbl_5_to_8[19] = 156;
   filt->tbl_5_to_8[20] = 165;
   filt->tbl_5_to_8[21] = 173;
   filt->tbl_5_to_8[22] = 181;
   filt->tbl_5_to_8[23] = 189;
   filt->tbl_5_to_8[24] = 197;
   filt->tbl_5_to_8[25] = 206;
   filt->tbl_5_to_8[26] = 214;
   filt->tbl_5_to_8[27] = 222;
   filt->tbl_5_to_8[28] = 230;
   filt->tbl_5_to_8[29] = 239;
   filt->tbl_5_to_8[30] = 247;
   filt->tbl_5_to_8[31] = 255;

   filt->tbl_6_to_8[0]   = 0;
   filt->tbl_6_to_8[1]   = 4;
   filt->tbl_6_to_8[2]   = 8;
   filt->tbl_6_to_8[3]   = 12;
   filt->tbl_6_to_8[4]   = 16;
   filt->tbl_6_to_8[5]   = 20;
   filt->tbl_6_to_8[6]   = 24;
   filt->tbl_6_to_8[7]   = 28;
   filt->tbl_6_to_8[8]   = 32;
   filt->tbl_6_to_8[9]   = 36;
   filt->tbl_6_to_8[10]  = 40;
   filt->tbl_6_to_8[11]  = 45;
   filt->tbl_6_to_8[12]  = 49;
   filt->tbl_6_to_8[13]  = 53;
   filt->tbl_6_to_8[14]  = 57;
   filt->tbl_6_to_8[15]  = 61;
   filt->tbl_6_to_8[16]  = 65;
   filt->tbl_6_to_8[17]  = 69;
   filt->tbl_6_to_8[18]  = 73;
   filt->tbl_6_to_8[19]  = 77;
   filt->tbl_6_to_8[20]  = 81;
   filt->tbl_6_to_8[21]  = 85;
   filt->tbl_6_to_8[22]  = 89;
   filt->tbl_6_to_8[23]  = 93;
   filt->tbl_6_to_8[24]  = 97;
   filt->tbl_6_to_8[25]  = 101;
   filt->tbl_6_to_8[26]  = 105;
   filt->tbl_6_to_8[27]  = 109;
   filt->tbl_6_to_8[28]  = 113;
   filt->tbl_6_to_8[29]  = 117;
   filt->tbl_6_to_8[30]  = 121;
   filt->tbl_6_to_8[31]  = 125;
   filt->tbl_6_to_8[32]  = 130;
   filt->tbl_6_to_8[33]  = 134;
   filt->tbl_6_to_8[34]  = 138;
   filt->tbl_6_to_8[35]  = 142;
   filt->tbl_6_to_8[36]  = 146;
   filt->tbl_6_to_8[37]  = 150;
   filt->tbl_6_to_8[38]  = 154;
   filt->tbl_6_to_8[39]  = 158;
   filt->tbl_6_to_8[40]  = 162;
   filt->tbl_6_to_8[41]  = 166;
   filt->tbl_6_to_8[42]  = 170;
   filt->tbl_6_to_8[43]  = 174;
   filt->tbl_6_to_8[44]  = 178;
   filt->tbl_6_to_8[45]  = 182;
   filt->tbl_6_to_8[46]  = 186;
   filt->tbl_6_to_8[47]  = 190;
   filt->tbl_6_to_8[48]  = 194;
   filt->tbl_6_to_8[49]  = 198;
   filt->tbl_6_to_8[50]  = 202;
   filt->tbl_6_to_8[51]  = 206;
   filt->tbl_6_to_8[52]  = 210;
   filt->tbl_6_to_8[53]  = 215;
   filt->tbl_6_to_8[54]  = 219;
   filt->tbl_6_to_8[55]  = 223;
   filt->tbl_6_to_8[56]  = 227;
   filt->tbl_6_to_8[57]  = 231;
   filt->tbl_6_to_8[58]  = 235;
   filt->tbl_6_to_8[59]  = 239;
   filt->tbl_6_to_8[60]  = 243;
   filt->tbl_6_to_8[61]  = 247;
   filt->tbl_6_to_8[62]  = 251;
   filt->tbl_6_to_8[63]  = 255;

   for (c = 0; c < 65536; c++)
   {
      uint16_t r = filt->tbl_5_to_8[(c &   RED_MASK565) >> 11];
      uint16_t g = filt->tbl_6_to_8[(c & GREEN_MASK565) >>  5];
      uint16_t b = filt->tbl_5_to_8[(c &  BLUE_MASK565)      ];
      uint16_t y = ((r << 4) + (g << 5) + (b << 2));
      uint16_t u = (   -r  - (g << 1) + (b << 2));
      uint16_t v = ((r << 1) - (g << 1) - (b >> 1));
      filt->RGBtoYUV[c] = y + u + v;
   }
}