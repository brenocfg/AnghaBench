#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  functionname; int /*<<< orphan*/  linenumber; scalar_t__ filename; scalar_t__ hint; scalar_t__ detail; scalar_t__ message; int /*<<< orphan*/  code; } ;
struct TYPE_6__ {int elevel; int /*<<< orphan*/  assoc_context; int /*<<< orphan*/  funcname; int /*<<< orphan*/  lineno; void* filename; void* hint; void* detail; void* message; int /*<<< orphan*/  sqlerrcode; } ;
typedef  TYPE_1__ ErrorData ;
typedef  TYPE_2__ DeferredErrorMessage ;

/* Variables and functions */
 int /*<<< orphan*/  ErrorContext ; 
 int /*<<< orphan*/  ThrowErrorData (TYPE_1__*) ; 
 TYPE_1__* palloc0 (int) ; 
 void* pstrdup (scalar_t__) ; 

void
RaiseDeferredErrorInternal(DeferredErrorMessage *error, int elevel)
{
	ErrorData *errorData = palloc0(sizeof(ErrorData));

	errorData->sqlerrcode = error->code;
	errorData->elevel = elevel;
	errorData->message = pstrdup(error->message);
	if (error->detail)
	{
		errorData->detail = pstrdup(error->detail);
	}
	if (error->hint)
	{
		errorData->hint = pstrdup(error->hint);
	}
	errorData->filename = pstrdup(error->filename);
	errorData->lineno = error->linenumber;
	errorData->funcname = error->functionname;

	errorData->assoc_context = ErrorContext;

	ThrowErrorData(errorData);
}