#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  file; } ;
typedef  int /*<<< orphan*/  JSON_Writer_HandlerResult ;
typedef  int /*<<< orphan*/  JSON_Writer ;
typedef  TYPE_1__ JSONContext ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_Writer_Abort ; 
 int /*<<< orphan*/  JSON_Writer_Continue ; 
 scalar_t__ JSON_Writer_GetUserData (int /*<<< orphan*/ ) ; 
 size_t filestream_write (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static JSON_Writer_HandlerResult JSONOutputHandler(JSON_Writer writer, const char *pBytes, size_t length)
{
   JSONContext *context = (JSONContext*)JSON_Writer_GetUserData(writer);

   (void)writer; /* unused */
   return filestream_write(context->file, pBytes, length) == length ? JSON_Writer_Continue : JSON_Writer_Abort;
}