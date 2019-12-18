#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
struct TYPE_4__ {int* bits; } ;
typedef  TYPE_1__ format_list ;

/* Variables and functions */
 int FORMAT_COUNT ; 
 int FORMAT_SET_COUNT ; 
 int PNG_FORMAT_FLAG_AFIRST ; 
 int PNG_FORMAT_FLAG_ALPHA ; 
 int PNG_FORMAT_FLAG_BGR ; 
 int PNG_FORMAT_FLAG_COLOR ; 
 int /*<<< orphan*/  format_set (TYPE_1__*,int) ; 

__attribute__((used)) static void format_default(format_list *pf, int redundant)
{
   if (redundant)
   {
      int i;

      /* set everything, including flags that are pointless */
      for (i=0; i<FORMAT_SET_COUNT; ++i)
         pf->bits[i] = ~(png_uint_32)0;
   }

   else
   {
      png_uint_32 f;

      for (f=0; f<FORMAT_COUNT; ++f)
      {
         /* Eliminate redundant and unsupported settings. */
#        ifdef PNG_FORMAT_BGR_SUPPORTED
            /* BGR is meaningless if no color: */
            if ((f & PNG_FORMAT_FLAG_COLOR) == 0 &&
               (f & PNG_FORMAT_FLAG_BGR) != 0)
#        else
            if ((f & 0x10U/*HACK: fixed value*/) != 0)
#        endif
            continue;

         /* AFIRST is meaningless if no alpha: */
#        ifdef PNG_FORMAT_AFIRST_SUPPORTED
            if ((f & PNG_FORMAT_FLAG_ALPHA) == 0 &&
               (f & PNG_FORMAT_FLAG_AFIRST) != 0)
#        else
            if ((f & 0x20U/*HACK: fixed value*/) != 0)
#        endif
            continue;

         format_set(pf, f);
      }
   }
}