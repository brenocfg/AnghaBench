#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* WriteBuffer ;
struct TYPE_8__ {int /*<<< orphan*/  outputEncoding; } ;
struct TYPE_7__ {int used; int /*<<< orphan*/ * bytes; } ;
typedef  TYPE_2__* JSON_Writer ;
typedef  int /*<<< orphan*/  JSON_Status ;
typedef  int /*<<< orphan*/  Codepoint ;

/* Variables and functions */
 scalar_t__ EncodeCodepoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JSON_Failure ; 
 int /*<<< orphan*/  JSON_Success ; 
 int LONGEST_ENCODING_SEQUENCE ; 
 int /*<<< orphan*/  WriteBuffer_Flush (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static JSON_Status WriteBuffer_WriteCodepoint(WriteBuffer buffer, JSON_Writer writer, Codepoint c)
{
   if (buffer->used + LONGEST_ENCODING_SEQUENCE > sizeof(buffer->bytes) &&
         !WriteBuffer_Flush(buffer, writer))
      return JSON_Failure;

   buffer->used += EncodeCodepoint(c, writer->outputEncoding, &buffer->bytes[buffer->used]);
   return JSON_Success;
}