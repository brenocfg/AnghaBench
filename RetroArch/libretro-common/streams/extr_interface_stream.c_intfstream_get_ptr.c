#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  fp; } ;
struct TYPE_5__ {int type; TYPE_1__ memory; } ;
typedef  TYPE_2__ intfstream_internal_t ;
typedef  int int64_t ;

/* Variables and functions */
#define  INTFSTREAM_CHD 130 
#define  INTFSTREAM_FILE 129 
#define  INTFSTREAM_MEMORY 128 
 int memstream_get_ptr (int /*<<< orphan*/ ) ; 

int64_t intfstream_get_ptr(intfstream_internal_t* intf)
{
   if (!intf)
      return 0;

   switch (intf->type)
   {
      case INTFSTREAM_FILE:
         return -1;
      case INTFSTREAM_MEMORY:
         return memstream_get_ptr(intf->memory.fp);
      case INTFSTREAM_CHD:
         return -1;
   }

   return 0;
}