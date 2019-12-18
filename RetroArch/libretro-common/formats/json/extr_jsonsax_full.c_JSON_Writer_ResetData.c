#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  state; int /*<<< orphan*/ * outputHandler; int /*<<< orphan*/  grammarianData; int /*<<< orphan*/  error; int /*<<< orphan*/  outputEncoding; int /*<<< orphan*/  flags; int /*<<< orphan*/ * userData; } ;
typedef  TYPE_1__* JSON_Writer ;

/* Variables and functions */
 int /*<<< orphan*/  Grammarian_Reset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  JSON_Error_None ; 
 int /*<<< orphan*/  JSON_UTF8 ; 
 int /*<<< orphan*/  WRITER_DEFAULT_FLAGS ; 
 int /*<<< orphan*/  WRITER_RESET ; 

__attribute__((used)) static void JSON_Writer_ResetData(JSON_Writer writer, int isInitialized)
{
   writer->userData = NULL;
   writer->flags = WRITER_DEFAULT_FLAGS;
   writer->outputEncoding = JSON_UTF8;
   writer->error = JSON_Error_None;
   Grammarian_Reset(&writer->grammarianData, isInitialized);
   writer->outputHandler = NULL;
   writer->state = WRITER_RESET; /* do this last! */
}