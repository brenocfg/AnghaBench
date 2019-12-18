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
struct TYPE_8__ {int /*<<< orphan*/  fp; } ;
struct TYPE_7__ {int /*<<< orphan*/  fp; } ;
struct TYPE_6__ {int /*<<< orphan*/  fp; } ;
struct TYPE_9__ {int type; TYPE_3__ chd; TYPE_2__ memory; TYPE_1__ file; } ;
typedef  TYPE_4__ intfstream_internal_t ;

/* Variables and functions */
#define  INTFSTREAM_CHD 130 
#define  INTFSTREAM_FILE 129 
#define  INTFSTREAM_MEMORY 128 
 int /*<<< orphan*/  chdstream_close (int /*<<< orphan*/ ) ; 
 int filestream_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memstream_close (int /*<<< orphan*/ ) ; 

int intfstream_close(intfstream_internal_t *intf)
{
   if (!intf)
      return -1;

   switch (intf->type)
   {
      case INTFSTREAM_FILE:
         if (intf->file.fp)
            return filestream_close(intf->file.fp);
         return 0;
      case INTFSTREAM_MEMORY:
         if (intf->memory.fp)
            memstream_close(intf->memory.fp);
         return 0;
      case INTFSTREAM_CHD:
#ifdef HAVE_CHD
         if (intf->chd.fp)
            chdstream_close(intf->chd.fp);
#endif
         return 0;
   }

   return -1;
}