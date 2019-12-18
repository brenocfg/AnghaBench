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
struct TYPE_7__ {int /*<<< orphan*/  fp; int /*<<< orphan*/  track; } ;
struct TYPE_6__ {int /*<<< orphan*/  fp; int /*<<< orphan*/  writable; } ;
struct TYPE_8__ {int /*<<< orphan*/  fp; } ;
struct TYPE_9__ {int type; TYPE_2__ chd; TYPE_1__ memory; TYPE_3__ file; } ;
typedef  TYPE_4__ intfstream_internal_t ;

/* Variables and functions */
#define  INTFSTREAM_CHD 130 
#define  INTFSTREAM_FILE 129 
#define  INTFSTREAM_MEMORY 128 
 int /*<<< orphan*/  chdstream_open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filestream_open (char const*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  memstream_open (int /*<<< orphan*/ ) ; 

bool intfstream_open(intfstream_internal_t *intf, const char *path,
      unsigned mode, unsigned hints)
{
   if (!intf)
      return false;

   switch (intf->type)
   {
      case INTFSTREAM_FILE:
         intf->file.fp = filestream_open(path, mode, hints);
         if (!intf->file.fp)
            return false;
         break;
      case INTFSTREAM_MEMORY:
         intf->memory.fp = memstream_open(intf->memory.writable);
         if (!intf->memory.fp)
            return false;
         break;
      case INTFSTREAM_CHD:
#ifdef HAVE_CHD
         intf->chd.fp = chdstream_open(path, intf->chd.track);
         if (!intf->chd.fp)
            return false;
         break;
#else
         return false;
#endif
   }

   return true;
}