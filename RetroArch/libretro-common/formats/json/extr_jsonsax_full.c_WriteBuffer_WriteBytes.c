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
typedef  int /*<<< orphan*/  byte ;
typedef  TYPE_1__* WriteBuffer ;
struct TYPE_4__ {size_t used; int /*<<< orphan*/ * bytes; } ;
typedef  int /*<<< orphan*/  JSON_Writer ;
typedef  int /*<<< orphan*/  JSON_Status ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_Failure ; 
 int /*<<< orphan*/  JSON_Success ; 
 int /*<<< orphan*/  WriteBuffer_Flush (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static JSON_Status WriteBuffer_WriteBytes(WriteBuffer buffer, JSON_Writer writer, const byte* pBytes, size_t length)
{
   if (buffer->used + length > sizeof(buffer->bytes) &&
         !WriteBuffer_Flush(buffer, writer))
      return JSON_Failure;

   memcpy(&buffer->bytes[buffer->used], pBytes, length);
   buffer->used += length;
   return JSON_Success;
}