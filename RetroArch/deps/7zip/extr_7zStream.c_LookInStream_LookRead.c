#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  (* Skip ) (TYPE_1__*,size_t) ;int /*<<< orphan*/  (* Look ) (TYPE_1__*,void const**,size_t*) ;} ;
typedef  int /*<<< orphan*/  SRes ;
typedef  TYPE_1__ ILookInStream ;

/* Variables and functions */
 int /*<<< orphan*/  RINOK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SZ_OK ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,void const**,size_t*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,size_t) ; 

SRes LookInStream_LookRead(ILookInStream *stream, void *buf, size_t *size)
{
   const void *lookBuf;
   if (*size == 0)
      return SZ_OK;
   RINOK(stream->Look(stream, &lookBuf, size));
   memcpy(buf, lookBuf, *size);
   return stream->Skip(stream, *size);
}