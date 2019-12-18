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
struct TYPE_5__ {scalar_t__ (* outputHandler ) (TYPE_1__*,char const*,size_t) ;} ;
typedef  TYPE_1__* JSON_Writer ;
typedef  int /*<<< orphan*/  JSON_Status ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_Error_AbortedByHandler ; 
 int /*<<< orphan*/  JSON_Failure ; 
 int /*<<< orphan*/  JSON_Success ; 
 scalar_t__ JSON_Writer_Continue ; 
 int /*<<< orphan*/  JSON_Writer_SetError (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_1__*,char const*,size_t) ; 

__attribute__((used)) static JSON_Status JSON_Writer_OutputBytes(JSON_Writer writer, const byte* pBytes, size_t length)
{
   if (writer->outputHandler && length)
   {
      if (writer->outputHandler(writer, (const char*)pBytes, length) != JSON_Writer_Continue)
      {
         JSON_Writer_SetError(writer, JSON_Error_AbortedByHandler);
         return JSON_Failure;
      }
   }
   return JSON_Success;
}