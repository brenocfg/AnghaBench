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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  fp; } ;
struct TYPE_7__ {int /*<<< orphan*/  fp; } ;
struct TYPE_6__ {int /*<<< orphan*/  fp; } ;
struct TYPE_9__ {int type; TYPE_3__ chd; TYPE_2__ memory; TYPE_1__ file; } ;
typedef  TYPE_4__ intfstream_internal_t ;
typedef  int int64_t ;

/* Variables and functions */
#define  INTFSTREAM_CHD 130 
#define  INTFSTREAM_FILE 129 
#define  INTFSTREAM_MEMORY 128 
 int chdstream_read (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int filestream_read (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int memstream_read (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

int64_t intfstream_read(intfstream_internal_t *intf, void *s, uint64_t len)
{
   if (!intf)
      return 0;

   switch (intf->type)
   {
      case INTFSTREAM_FILE:
         return filestream_read(intf->file.fp, s, len);
      case INTFSTREAM_MEMORY:
         return memstream_read(intf->memory.fp, s, len);
      case INTFSTREAM_CHD:
#ifdef HAVE_CHD
         return chdstream_read(intf->chd.fp, s, len);
#else
         break;
#endif
   }

   return -1;
}