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

int FONT_alignRight(char *string, int size, int x, int y, GXColor color)
{
  int i;
  int w = 0;

  x -= (vmode->fbWidth / 2);
  y -= (vmode->efbHeight / 2);

  int ox = x;

  for (i=0; i<strlen(string); i++)
  {
    w += (font_size[(u8)string[i]] * size) / fheight;
  }

  x = ox - w;

  while (*string)
  {
    w = (font_size[(u8)*string] * size) / fheight;
    if ((x + w) > ox) return strlen(string);
    DrawChar(*string, x, y, size,color);
    x += w;
    string++;
  }
  return 0;
}