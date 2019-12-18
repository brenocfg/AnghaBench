#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_4__ {size_t NumTokens; char** Token; } ;
typedef  TYPE_1__ TOKEN_LIST ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  JSON_VALUE ;
typedef  int /*<<< orphan*/  JSON_OBJECT ;

/* Variables and functions */
 scalar_t__ AddStrToStrListDistinct (int /*<<< orphan*/ *,char*) ; 
 char* CopyStr (char*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeStrList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeToken (TYPE_1__*) ; 
 size_t INFINITE ; 
 int /*<<< orphan*/ * JsonNewObject () ; 
 int /*<<< orphan*/  JsonSetStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * JsonValueGetObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewStrList () ; 
 TYPE_1__* ParseTokenWithoutNullStr (char*,char*) ; 
 size_t SearchStr (char*,char*,int /*<<< orphan*/ ) ; 
 char* UrlDecode (char*) ; 

JSON_VALUE *QueryStringToJsonListValue(char *qs)
{
	TOKEN_LIST *t;
	UINT i;
	LIST *distinct_list = NULL;
	JSON_VALUE *v = NULL;
	JSON_OBJECT *o = NULL;
	if (qs == NULL)
	{
		return NULL;
	}

	t = ParseTokenWithoutNullStr(qs, "&");
	if (t == NULL)
	{
		return NULL;
	}

	distinct_list = NewStrList();

	v = JsonNewObject();
	o = JsonValueGetObject(v);

	for (i = 0;i < t->NumTokens;i++)
	{
		char *token = t->Token[i];
		UINT pos;

		pos = SearchStr(token, "=", 0);
		if (pos != INFINITE)
		{
			char *key_decoded;
			char *value_decoded;
			char *key = CopyStr(token);
			char *value = CopyStr(token + pos + 1);

			key[pos] = 0;
			key_decoded = UrlDecode(key);
			value_decoded = UrlDecode(value);

			if (key_decoded != NULL && value_decoded != NULL)
			{
				if (AddStrToStrListDistinct(distinct_list, key_decoded))
				{
					JsonSetStr(o, key_decoded, value_decoded);
				}
			}

			Free(value_decoded);
			Free(key_decoded);
			Free(key);
			Free(value);
		}
	}

	FreeToken(t);

	FreeStrList(distinct_list);

	return v;
}