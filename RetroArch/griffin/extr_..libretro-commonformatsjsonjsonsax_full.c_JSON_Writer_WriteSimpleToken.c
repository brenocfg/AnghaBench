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
typedef  int /*<<< orphan*/  byte ;
struct TYPE_5__ {scalar_t__ error; int outputEncoding; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  Symbol ;
typedef  TYPE_1__* JSON_Writer ;
typedef  int /*<<< orphan*/  JSON_Status ;

/* Variables and functions */
 int /*<<< orphan*/  GET_FLAGS (int /*<<< orphan*/ ,int) ; 
 scalar_t__ JSON_Error_None ; 
 int /*<<< orphan*/  JSON_Failure ; 
 int /*<<< orphan*/  JSON_Success ; 
 scalar_t__ JSON_Writer_OutputBytes (TYPE_1__*,int /*<<< orphan*/  const* const,size_t) ; 
 scalar_t__ JSON_Writer_ProcessToken (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_FLAGS_OFF (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_FLAGS_ON (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ SHORTEST_ENCODING_SEQUENCE (int) ; 
 int WRITER_IN_PROTECTED_API ; 
 int WRITER_STARTED ; 
 int /*<<< orphan*/  WriterState ; 

__attribute__((used)) static JSON_Status JSON_Writer_WriteSimpleToken(JSON_Writer writer, Symbol token, const byte* const* encodings, size_t length)
{
   JSON_Status status = JSON_Failure;
   if (writer && !GET_FLAGS(writer->state, WRITER_IN_PROTECTED_API) && writer->error == JSON_Error_None)
   {
      size_t encodedLength = length * (size_t)SHORTEST_ENCODING_SEQUENCE(writer->outputEncoding);
      SET_FLAGS_ON(WriterState, writer->state, WRITER_STARTED | WRITER_IN_PROTECTED_API);
      if (JSON_Writer_ProcessToken(writer, token) &&
            JSON_Writer_OutputBytes(writer, encodings[writer->outputEncoding - 1], encodedLength))
         status = JSON_Success;
      SET_FLAGS_OFF(WriterState, writer->state, WRITER_IN_PROTECTED_API);
   }
   return status;
}