#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_11__ {TYPE_4__ buf; } ;
struct TYPE_13__ {int type; TYPE_3__ memory; } ;
typedef  TYPE_5__ intfstream_internal_t ;
struct TYPE_9__ {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
struct TYPE_10__ {TYPE_1__ buf; } ;
struct TYPE_14__ {TYPE_2__ memory; } ;
typedef  TYPE_6__ intfstream_info_t ;

/* Variables and functions */
#define  INTFSTREAM_CHD 130 
#define  INTFSTREAM_FILE 129 
#define  INTFSTREAM_MEMORY 128 
 int /*<<< orphan*/  memstream_set_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool intfstream_resize(intfstream_internal_t *intf, intfstream_info_t *info)
{
   if (!intf || !info)
      return false;

   switch (intf->type)
   {
      case INTFSTREAM_FILE:
         break;
      case INTFSTREAM_MEMORY:
         intf->memory.buf.data = info->memory.buf.data;
         intf->memory.buf.size = info->memory.buf.size;

         memstream_set_buffer(intf->memory.buf.data,
               intf->memory.buf.size);
         break;
      case INTFSTREAM_CHD:
#ifdef HAVE_CHD
#endif
         break;
   }

   return true;
}