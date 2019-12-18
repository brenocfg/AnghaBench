#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {double X; double Y; double Z; } ;
struct TYPE_7__ {double X; double Y; double Z; } ;
struct TYPE_6__ {double X; double Y; double Z; } ;
struct TYPE_9__ {TYPE_3__ blue; TYPE_2__ green; TYPE_1__ red; } ;
typedef  TYPE_4__ color_encoding ;

/* Variables and functions */
 size_t safecat (char*,size_t,size_t,char*) ; 
 size_t safecatd (char*,size_t,size_t,double,int) ; 

__attribute__((used)) static size_t
safecat_color_encoding(char *buffer, size_t bufsize, size_t pos,
   const color_encoding *e, double encoding_gamma)
{
   if (e != 0)
   {
      if (encoding_gamma != 0)
         pos = safecat(buffer, bufsize, pos, "(");
      pos = safecat(buffer, bufsize, pos, "R(");
      pos = safecatd(buffer, bufsize, pos, e->red.X, 4);
      pos = safecat(buffer, bufsize, pos, ",");
      pos = safecatd(buffer, bufsize, pos, e->red.Y, 4);
      pos = safecat(buffer, bufsize, pos, ",");
      pos = safecatd(buffer, bufsize, pos, e->red.Z, 4);
      pos = safecat(buffer, bufsize, pos, "),G(");
      pos = safecatd(buffer, bufsize, pos, e->green.X, 4);
      pos = safecat(buffer, bufsize, pos, ",");
      pos = safecatd(buffer, bufsize, pos, e->green.Y, 4);
      pos = safecat(buffer, bufsize, pos, ",");
      pos = safecatd(buffer, bufsize, pos, e->green.Z, 4);
      pos = safecat(buffer, bufsize, pos, "),B(");
      pos = safecatd(buffer, bufsize, pos, e->blue.X, 4);
      pos = safecat(buffer, bufsize, pos, ",");
      pos = safecatd(buffer, bufsize, pos, e->blue.Y, 4);
      pos = safecat(buffer, bufsize, pos, ",");
      pos = safecatd(buffer, bufsize, pos, e->blue.Z, 4);
      pos = safecat(buffer, bufsize, pos, ")");
      if (encoding_gamma != 0)
         pos = safecat(buffer, bufsize, pos, ")");
   }

   if (encoding_gamma != 0)
   {
      pos = safecat(buffer, bufsize, pos, "^");
      pos = safecatd(buffer, bufsize, pos, encoding_gamma, 5);
   }

   return pos;
}