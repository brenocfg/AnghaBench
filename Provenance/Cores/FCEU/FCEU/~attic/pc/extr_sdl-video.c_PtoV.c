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
typedef  int uint32 ;
typedef  int uint16 ;

/* Variables and functions */
 int EO_CLIPSIDES ; 
 int eoptions ; 
 double exs ; 
 double eys ; 
 scalar_t__ srendline ; 

uint32 PtoV(uint16 x, uint16 y)
{
 y=(double)y/eys;
 x=(double)x/exs;
 if(eoptions&EO_CLIPSIDES)
  x+=8;
 y+=srendline;
 return(x|(y<<16));
}