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
struct TYPE_2__ {int r; int g; int b; } ;

/* Variables and functions */
 TYPE_1__* palette ; 
 int /*<<< orphan*/  printf (char*,int,int,int) ; 
 int* rp2c04001_colortable ; 

main()
{
 int x;
 for(x=0;x<64;x++)
 {
 // if(x <= 0x20)
//  if(rp2c04002_colortable[x] == 0xFF) rp2c04002_colortable[x]= 0x30;
  printf("{0x%02x, 0x%02x, 0x%02x},\n",palette[rp2c04001_colortable[x]&0x3F].r,
				 palette[rp2c04001_colortable[x]&0x3F].g,
				 palette[rp2c04001_colortable[x]&0x3F].b);
 }
}