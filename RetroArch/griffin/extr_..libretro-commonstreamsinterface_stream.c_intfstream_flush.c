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
struct TYPE_5__ {int type; TYPE_1__ file; } ;
typedef  TYPE_2__ intfstream_internal_t ;

/* Variables and functions */
#define  INTFSTREAM_CHD 130 
#define  INTFSTREAM_FILE 129 
#define  INTFSTREAM_MEMORY 128 
 int filestream_flush (int /*<<< orphan*/ ) ; 

int intfstream_flush(intfstream_internal_t *intf)
{
   if (!intf)
      return -1;

   switch (intf->type)
   {
      case INTFSTREAM_FILE:
         return filestream_flush(intf->file.fp);
      case INTFSTREAM_MEMORY:
      case INTFSTREAM_CHD:
         /* Should we stub this for these interfaces? */
         break;
   }

   return 0;
}