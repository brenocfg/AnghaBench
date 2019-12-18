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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* Read ) (TYPE_1__*,void*,size_t*) ;} ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ ILookInStream ;

/* Variables and functions */
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,void*,size_t*) ; 

SRes LookInStream_Read2(ILookInStream *stream, void *buf, size_t size, SRes errorType)
{
   while (size != 0)
   {
      size_t processed = size;
      RINOK(stream->Read(stream, buf, &processed));
      if (processed == 0)
         return errorType;
      buf = (void *)((uint8_t *)buf + processed);
      size -= processed;
   }
   return SZ_OK;
}