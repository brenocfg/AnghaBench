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

/* Variables and functions */
 int /*<<< orphan*/  paethPredictor (unsigned char const,unsigned char const,unsigned char const) ; 

__attribute__((used)) static void filterScanline(unsigned char* out, const unsigned char* scanline, const unsigned char* prevline,
                           size_t length, size_t bytewidth, unsigned char filterType)
{
  size_t i;
  switch(filterType)
  {
    case 0: /*None*/
      for(i = 0; i < length; i++) out[i] = scanline[i];
      break;
    case 1: /*Sub*/
      if(prevline)
      {
        for(i = 0; i < bytewidth; i++) out[i] = scanline[i];
        for(i = bytewidth; i < length; i++) out[i] = scanline[i] - scanline[i - bytewidth];
      }
      else
      {
        for(i = 0; i < bytewidth; i++) out[i] = scanline[i];
        for(i = bytewidth; i < length; i++) out[i] = scanline[i] - scanline[i - bytewidth];
      }
      break;
    case 2: /*Up*/
      if(prevline)
      {
        for(i = 0; i < length; i++) out[i] = scanline[i] - prevline[i];
      }
      else
      {
        for(i = 0; i < length; i++) out[i] = scanline[i];
      }
      break;
    case 3: /*Average*/
      if(prevline)
      {
        for(i = 0; i < bytewidth; i++) out[i] = scanline[i] - prevline[i] / 2;
        for(i = bytewidth; i < length; i++) out[i] = scanline[i] - ((scanline[i - bytewidth] + prevline[i]) / 2);
      }
      else
      {
        for(i = 0; i < bytewidth; i++) out[i] = scanline[i];
        for(i = bytewidth; i < length; i++) out[i] = scanline[i] - scanline[i - bytewidth] / 2;
      }
      break;
    case 4: /*Paeth*/
      if(prevline)
      {
        /*paethPredictor(0, prevline[i], 0) is always prevline[i]*/
        for(i = 0; i < bytewidth; i++) out[i] = (scanline[i] - prevline[i]);
        for(i = bytewidth; i < length; i++)
        {
          out[i] = (scanline[i] - paethPredictor(scanline[i - bytewidth], prevline[i], prevline[i - bytewidth]));
        }
      }
      else
      {
        for(i = 0; i < bytewidth; i++) out[i] = scanline[i];
        /*paethPredictor(scanline[i - bytewidth], 0, 0) is always scanline[i - bytewidth]*/
        for(i = bytewidth; i < length; i++) out[i] = (scanline[i] - scanline[i - bytewidth]);
      }
      break;
    default: return; /*unexisting filter type given*/
  }
}