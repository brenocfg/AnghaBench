#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  string; } ;
typedef  TYPE_1__ token_t ;
struct TYPE_11__ {int /*<<< orphan*/  size; int /*<<< orphan*/  fields; } ;
typedef  TYPE_2__ structdef_t ;
typedef  int /*<<< orphan*/  source_t ;
struct TYPE_12__ {int type; int maxarray; int offset; TYPE_2__* substruct; } ;
typedef  TYPE_3__ fielddef_t ;

/* Variables and functions */
 int FT_ARRAY ; 
#define  FT_CHAR 132 
#define  FT_FLOAT 131 
#define  FT_INT 130 
#define  FT_STRING 129 
#define  FT_STRUCT 128 
 int FT_TYPE ; 
 TYPE_3__* FindField (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_STRINGFIELD ; 
 scalar_t__ PC_CheckTokenString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PC_ExpectAnyToken (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  PC_ExpectTokenString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ReadChar (int /*<<< orphan*/ *,TYPE_3__*,void*) ; 
 int /*<<< orphan*/  ReadNumber (int /*<<< orphan*/ *,TYPE_3__*,void*) ; 
 int /*<<< orphan*/  ReadString (int /*<<< orphan*/ *,TYPE_3__*,void*) ; 
 int /*<<< orphan*/  SourceError (int /*<<< orphan*/ *,char*,...) ; 
 int qfalse ; 
 int qtrue ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

int ReadStructure(source_t *source, structdef_t *def, char *structure)
{
	token_t token;
	fielddef_t *fd;
	void *p;
	int num;

	if (!PC_ExpectTokenString(source, "{")) return 0;
	while(1)
	{
		if (!PC_ExpectAnyToken(source, &token)) return qfalse;
		//if end of structure
		if (!strcmp(token.string, "}")) break;
		//find the field with the name
		fd = FindField(def->fields, token.string);
		if (!fd)
		{
			SourceError(source, "unknown structure field %s", token.string);
			return qfalse;
		} //end if
		if (fd->type & FT_ARRAY)
		{
			num = fd->maxarray;
			if (!PC_ExpectTokenString(source, "{")) return qfalse;
		} //end if
		else
		{
			num = 1;
		} //end else
		p = (void *)(structure + fd->offset);
		while (num-- > 0)
		{
			if (fd->type & FT_ARRAY)
			{
				if (PC_CheckTokenString(source, "}")) break;
			} //end if
			switch(fd->type & FT_TYPE)
			{
				case FT_CHAR:
				{
					if (!ReadChar(source, fd, p)) return qfalse;
					p = (char *) p + sizeof(char);
					break;
				} //end case
				case FT_INT:
				{
					if (!ReadNumber(source, fd, p)) return qfalse;
					p = (char *) p + sizeof(int);
					break;
				} //end case
				case FT_FLOAT:
				{
					if (!ReadNumber(source, fd, p)) return qfalse;
					p = (char *) p + sizeof(float);
					break;
				} //end case
				case FT_STRING:
				{
					if (!ReadString(source, fd, p)) return qfalse;
					p = (char *) p + MAX_STRINGFIELD;
					break;
				} //end case
				case FT_STRUCT:
				{
					if (!fd->substruct)
					{
						SourceError(source, "BUG: no sub structure defined");
						return qfalse;
					} //end if
					ReadStructure(source, fd->substruct, (char *) p);
					p = (char *) p + fd->substruct->size;
					break;
				} //end case
			} //end switch
			if (fd->type & FT_ARRAY)
			{
				if (!PC_ExpectAnyToken(source, &token)) return qfalse;
				if (!strcmp(token.string, "}")) break;
				if (strcmp(token.string, ","))
				{
					SourceError(source, "expected a comma, found %s", token.string);
					return qfalse;
				} //end if
			} //end if
		} //end while
	} //end while
	return qtrue;
}