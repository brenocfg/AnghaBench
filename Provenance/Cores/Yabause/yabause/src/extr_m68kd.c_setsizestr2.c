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
typedef  int u16 ;

/* Variables and functions */
 int sprintf (char*,char*) ; 

__attribute__((used)) static int setsizestr2(u16 size, char *outstring)
{
   switch (size & 0x3)
   {
      case 0x0:
         return sprintf(outstring, ".b ");
      case 0x1:
         return sprintf(outstring, ".w ");
      case 0x2:
         return sprintf(outstring, ".l ");
      default:
         return sprintf(outstring, " ");
   }
}