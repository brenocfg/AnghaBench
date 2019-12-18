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
typedef  size_t u8 ;
struct TYPE_2__ {int fbWidth; int efbHeight; } ;
typedef  int /*<<< orphan*/  GXColor ;

/* Variables and functions */
 int /*<<< orphan*/  DrawChar (char,int,int,int,int /*<<< orphan*/ ) ; 
 int fheight ; 
 int* font_size ; 
 int strlen (char*) ; 
 TYPE_1__* vmode ; 

int FONT_writeCenter(char *string, int size, int x1, int x2, int y, GXColor color)
{
  int i=0;
  int w = 0;
  while (string[i] && (string[i] != '\n'))
  {
    w += (font_size[(u8)string[i++]] * size) / fheight;
  }

  if ((x1 + w) > x2) w = x2 - x1;
  int x = x1 + (x2 - x1 - w - vmode->fbWidth) / 2;
  y  -= (vmode->efbHeight / 2);
  x2 -= (vmode->fbWidth / 2);

  while (*string && (*string != '\n'))
  {
    w = (font_size[(u8)*string] * size) / fheight;
    if ((x + w) > x2) return strlen(string);
    DrawChar(*string, x, y, size,color);
    x += w;
    string++;
  }

  if (*string == '\n')
  {
    string++;
    return FONT_writeCenter(string, size, x1, x2 + (vmode->fbWidth / 2), y + size + (vmode->efbHeight / 2), color);
  }
  return 0;
}