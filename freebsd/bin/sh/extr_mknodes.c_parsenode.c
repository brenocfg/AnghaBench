#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct str {scalar_t__ nfields; int done; void* tag; } ;

/* Variables and functions */
 int BUFLEN ; 
 struct str* curstr ; 
 int /*<<< orphan*/  error (char*) ; 
 char* linep ; 
 int /*<<< orphan*/  nextfield (char*) ; 
 void** nodename ; 
 struct str** nodestr ; 
 int nstr ; 
 size_t ntypes ; 
 void* savestr (char*) ; 
 struct str* str ; 
 scalar_t__ strcmp (void*,char*) ; 

__attribute__((used)) static void
parsenode(void)
{
	char name[BUFLEN];
	char tag[BUFLEN];
	struct str *sp;

	if (curstr && curstr->nfields > 0)
		curstr->done = 1;
	nextfield(name);
	if (! nextfield(tag))
		error("Tag expected");
	if (*linep != '\0')
		error("Garbage at end of line");
	nodename[ntypes] = savestr(name);
	for (sp = str ; sp < str + nstr ; sp++) {
		if (strcmp(sp->tag, tag) == 0)
			break;
	}
	if (sp >= str + nstr) {
		sp->tag = savestr(tag);
		sp->nfields = 0;
		curstr = sp;
		nstr++;
	}
	nodestr[ntypes] = sp;
	ntypes++;
}