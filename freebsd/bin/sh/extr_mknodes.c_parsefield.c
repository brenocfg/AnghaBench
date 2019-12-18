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
struct field {scalar_t__ type; void* decl; void* name; } ;
struct TYPE_2__ {size_t nfields; struct field* field; scalar_t__ done; } ;

/* Variables and functions */
 int BUFLEN ; 
 scalar_t__ T_INT ; 
 scalar_t__ T_NODE ; 
 scalar_t__ T_NODELIST ; 
 scalar_t__ T_OTHER ; 
 scalar_t__ T_STRING ; 
 scalar_t__ T_TEMP ; 
 TYPE_1__* curstr ; 
 int /*<<< orphan*/  error (char*,...) ; 
 char* linep ; 
 int /*<<< orphan*/  nextfield (char*) ; 
 void* savestr (char*) ; 
 int /*<<< orphan*/  skipbl () ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static void
parsefield(void)
{
	char name[BUFLEN];
	char type[BUFLEN];
	char decl[2 * BUFLEN];
	struct field *fp;

	if (curstr == NULL || curstr->done)
		error("No current structure to add field to");
	if (! nextfield(name))
		error("No field name");
	if (! nextfield(type))
		error("No field type");
	fp = &curstr->field[curstr->nfields];
	fp->name = savestr(name);
	if (strcmp(type, "nodeptr") == 0) {
		fp->type = T_NODE;
		sprintf(decl, "union node *%s", name);
	} else if (strcmp(type, "nodelist") == 0) {
		fp->type = T_NODELIST;
		sprintf(decl, "struct nodelist *%s", name);
	} else if (strcmp(type, "string") == 0) {
		fp->type = T_STRING;
		sprintf(decl, "char *%s", name);
	} else if (strcmp(type, "int") == 0) {
		fp->type = T_INT;
		sprintf(decl, "int %s", name);
	} else if (strcmp(type, "other") == 0) {
		fp->type = T_OTHER;
	} else if (strcmp(type, "temp") == 0) {
		fp->type = T_TEMP;
	} else {
		error("Unknown type %s", type);
	}
	if (fp->type == T_OTHER || fp->type == T_TEMP) {
		skipbl();
		fp->decl = savestr(linep);
	} else {
		if (*linep)
			error("Garbage at end of line");
		fp->decl = savestr(decl);
	}
	curstr->nfields++;
}