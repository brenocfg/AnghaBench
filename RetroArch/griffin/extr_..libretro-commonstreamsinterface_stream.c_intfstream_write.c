#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  fp; } ;
struct TYPE_5__ {int /*<<< orphan*/  fp; } ;
struct TYPE_7__ {int type; TYPE_2__ memory; TYPE_1__ file; } ;
typedef  TYPE_3__ intfstream_internal_t ;
typedef  int int64_t ;

/* Variables and functions */
#define  INTFSTREAM_CHD 130 
#define  INTFSTREAM_FILE 129 
#define  INTFSTREAM_MEMORY 128 
 int filestream_write (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 int memstream_write (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 

int64_t intfstream_write(intfstream_internal_t *intf,
      const void *s, uint64_t len)
{
   if (!intf)
      return 0;

   switch (intf->type)
   {
      case INTFSTREAM_FILE:
         return filestream_write(intf->file.fp, s, len);
      case INTFSTREAM_MEMORY:
         return memstream_write(intf->memory.fp, s, len);
      case INTFSTREAM_CHD:
         return -1;
   }

   return 0;
}