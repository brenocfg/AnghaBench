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
typedef  size_t UINT ;
struct TYPE_7__ {void* Value; void* Name; } ;
struct TYPE_6__ {size_t NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  TYPE_2__ STRMAP_ENTRY ;
typedef  int /*<<< orphan*/  LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 void* CopyStr (char*) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 scalar_t__ Malloc (int) ; 
 int /*<<< orphan*/ * NewStrMap () ; 
 TYPE_1__* ParseToken (char*,char*) ; 
 scalar_t__ StartWith (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,size_t,char*) ; 

__attribute__((used)) static LIST *WuAnalyzeTarget(char *target,char *filename, UINT size)
{
	char *start, tmp;

	if(target == NULL || filename == NULL)
	{
		return NULL;
	}

	// Process the absolute path specification
	if(StartWith(target,"http://"))
	{
		// Skip http://
		target += 7;

		// Skip the host name portion
		while(*target != '/' && *target != '\0')
		{
			target ++;
		}

		// Error if the "/" isn't included after "http://"
		if(*target == '\0')
		{
			return NULL;
		}

		target++;
	}

	// Unescape
	// (not implemented)

	// Extract the file name portion
	start = target;
	while(*target != '?' && *target != '\0')
	{
		target ++;
	}
	tmp = *target;
	*target = '\0';
	StrCpy(filename, size, start);
	*target = tmp;

	// Interpret if there are parameters
	if(*target == '?')
	{
		LIST *params = NewStrMap();
		UINT i;
		TOKEN_LIST *tl;
		target++;
		tl =ParseToken(target,"&");
		for(i=0;i<tl->NumTokens;i++)
		{
			char *token = tl->Token[i];
			char *body = token;
			STRMAP_ENTRY *newentry = (STRMAP_ENTRY*)Malloc(sizeof(STRMAP_ENTRY));

			while(*body != '=' && *body != '\0')
			{
				body++;
			}
			if(*body == '=')
			{
				*body = '\0';
				body++;
			}
			newentry->Name = CopyStr(token);
			newentry->Value = CopyStr(body);
			Add(params, newentry);
//			Debug("PARAMS: %s : %s\n",token,body);
		}
		FreeToken(tl);
		return params;
	}
	return NULL;
}