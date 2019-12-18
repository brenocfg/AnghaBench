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
typedef  int /*<<< orphan*/  GXColor ;

/* Variables and functions */
 int /*<<< orphan*/  FONT_writeCenter (char*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ WHITE ; 

__attribute__((used)) static void show_disclaimer(int ypos)
{
  FONT_writeCenter ("DISCLAIMER",22,0,640,ypos,(GXColor)WHITE);
  ypos += 32;
  FONT_writeCenter ("This is a free software, and you are welcome",20,0,640,ypos,(GXColor)WHITE);
  ypos += 20;
  FONT_writeCenter ("to redistribute it under the conditions of the",20,0,640,ypos,(GXColor)WHITE);
  ypos += 20;
  FONT_writeCenter ("license that you should have received with this",20,0,640,ypos,(GXColor)WHITE);
  ypos += 20;
  FONT_writeCenter ("program. You may not sell, lease, rent or generally",20,0,640,ypos,(GXColor)WHITE);
  ypos += 20;
  FONT_writeCenter ("use this software in any commercial product or activity.",20,0,640,ypos,(GXColor)WHITE);
  ypos += 20;
  FONT_writeCenter ("Authors can not be held responsible for any damage or",20,0,640,ypos,(GXColor)WHITE);
  ypos += 20;
  FONT_writeCenter ("or dysfunction that could occur while using this port.",20,0,640,ypos,(GXColor)WHITE);
  ypos += 20;
  FONT_writeCenter ("You may not distribute this software with any ROM image",20,0,640,ypos,(GXColor)WHITE);
  ypos += 20;
  FONT_writeCenter ("unless you have the legal right to distribute them.",20,0,640,ypos,(GXColor)WHITE);
  ypos += 20;
  FONT_writeCenter ("This software is not endorsed by or affiliated",20,0,640,ypos,(GXColor)WHITE);
  ypos += 20;
  FONT_writeCenter ("with Sega Enterprises Ltd or Nintendo Co Ltd.",20,0,640,ypos,(GXColor)WHITE);
  ypos += 20;
  FONT_writeCenter ("All trademarks and registered trademarks are",20,0,640,ypos,(GXColor)WHITE);
  ypos += 20;
  FONT_writeCenter ("the property of their respective owners.",20,0,640,ypos,(GXColor)WHITE);
  ypos += 38;
}