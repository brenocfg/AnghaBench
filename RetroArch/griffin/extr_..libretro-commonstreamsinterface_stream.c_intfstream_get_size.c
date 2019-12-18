#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  fp; } ;
struct TYPE_8__ {int /*<<< orphan*/  size; } ;
struct TYPE_9__ {TYPE_2__ buf; } ;
struct TYPE_7__ {int /*<<< orphan*/  fp; } ;
struct TYPE_11__ {int type; TYPE_4__ chd; TYPE_3__ memory; TYPE_1__ file; } ;
typedef  TYPE_5__ intfstream_internal_t ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
#define  INTFSTREAM_CHD 130 
#define  INTFSTREAM_FILE 129 
#define  INTFSTREAM_MEMORY 128 
 int /*<<< orphan*/  chdstream_get_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  filestream_get_size (int /*<<< orphan*/ ) ; 

int64_t intfstream_get_size(intfstream_internal_t *intf)
{
   if (!intf)
      return 0;

   switch (intf->type)
   {
      case INTFSTREAM_FILE:
         return filestream_get_size(intf->file.fp);
      case INTFSTREAM_MEMORY:
         return intf->memory.buf.size;
      case INTFSTREAM_CHD:
#ifdef HAVE_CHD
        return chdstream_get_size(intf->chd.fp);
#else
        break;
#endif
   }

   return 0;
}