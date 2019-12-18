#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
typedef  scalar_t__ UINT ;
struct TYPE_10__ {int num_value; char* JsonHint_GroupName; int /*<<< orphan*/  name; scalar_t__ JsonHint_IsArray; } ;
struct TYPE_9__ {int /*<<< orphan*/ * elements; int /*<<< orphan*/ * json_subitem_names; } ;
typedef  TYPE_1__ PACK ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  JSON_VALUE ;
typedef  int /*<<< orphan*/  JSON_OBJECT ;
typedef  int /*<<< orphan*/  JSON_ARRAY ;
typedef  TYPE_2__ ELEMENT ;

/* Variables and functions */
 int /*<<< orphan*/  AddStrToStrListDistinct (int /*<<< orphan*/ *,char*) ; 
 char* DetermineJsonSuffixForPackElement (TYPE_2__*) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ **) ; 
 scalar_t__ INFINITE ; 
 int IsEmptyStr (char*) ; 
 int /*<<< orphan*/ * JsonArray (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JsonArrayAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonNewArray () ; 
 int /*<<< orphan*/ * JsonNewObject () ; 
 int /*<<< orphan*/  JsonSet (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * JsonValueGetObject (int /*<<< orphan*/ *) ; 
 void* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/ * NewStrList () ; 
 int /*<<< orphan*/  PackArrayElementToJsonArray (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  PackElementToJsonObject (int /*<<< orphan*/ *,TYPE_1__*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  ReleaseStrList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrCat (char*,int,char*) ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** ZeroMalloc (int) ; 

JSON_VALUE *PackToJson(PACK *p)
{
	JSON_VALUE *v;
	JSON_OBJECT *o;
	UINT i, j, k;
	LIST *json_group_id_list;
	if (p == NULL)
	{
		return JsonNewObject();
	}

	json_group_id_list = NewStrList();

	for (i = 0;i < LIST_NUM(p->elements);i++)
	{
		ELEMENT *e = LIST_DATA(p->elements, i);

		if (e->num_value >= 2 || e->JsonHint_IsArray)
		{
			if (IsEmptyStr(e->JsonHint_GroupName) == false)
			{
				AddStrToStrListDistinct(json_group_id_list, e->JsonHint_GroupName);
			}
		}
	}

	for (i = 0;i < LIST_NUM(p->json_subitem_names);i++)
	{
		char *group_name = LIST_DATA(p->json_subitem_names, i);

		if (IsEmptyStr(group_name) == false)
		{
			AddStrToStrListDistinct(json_group_id_list, group_name);
		}
	}

	v = JsonNewObject();
	o = JsonValueGetObject(v);

	for (k = 0;k < LIST_NUM(json_group_id_list);k++)
	{
		char *group_name = LIST_DATA(json_group_id_list, k);
		UINT array_count = INFINITE;
		bool ok = true;

		for (i = 0;i < LIST_NUM(p->elements);i++)
		{
			ELEMENT *e = LIST_DATA(p->elements, i);

			if (e->num_value >= 2 || e->JsonHint_IsArray)
			{
				if (StrCmpi(e->JsonHint_GroupName, group_name) == 0)
				{
					if (array_count == INFINITE)
					{
						array_count = e->num_value;
					}
					else
					{
						if (array_count != e->num_value)
						{
							ok = false;
						}
					}
				}
			}
		}

		if (array_count == INFINITE)
		{
			array_count = 0;
		}

		if (ok)
		{
			JSON_VALUE **json_objects = ZeroMalloc(sizeof(void *) * array_count);
			JSON_VALUE *jav = JsonNewArray();
			JSON_ARRAY *ja = JsonArray(jav);

			JsonSet(o, group_name, jav);

			for (j = 0;j < array_count;j++)
			{
				json_objects[j] = JsonNewObject();

				JsonArrayAdd(ja, json_objects[j]);
			}

			for (i = 0;i < LIST_NUM(p->elements);i++)
			{
				ELEMENT *e = LIST_DATA(p->elements, i);

				if (e->num_value >= 2 || e->JsonHint_IsArray)
				{
					if (StrCmpi(e->JsonHint_GroupName, group_name) == 0)
					{
						for (j = 0;j < e->num_value;j++)
						{
							PackElementToJsonObject(JsonValueGetObject(json_objects[j]),
								p, e, j);
						}
					}
				}
			}

			Free(json_objects);
		}
	}

	for (i = 0;i < LIST_NUM(p->elements);i++)
	{
		ELEMENT *e = LIST_DATA(p->elements, i);

		if (e->num_value >= 2 || e->JsonHint_IsArray)
		{
			if (IsEmptyStr(e->JsonHint_GroupName))
			{
				char *suffix = DetermineJsonSuffixForPackElement(e);

				if (suffix != NULL)
				{
					JSON_VALUE *jav = JsonNewArray();
					JSON_ARRAY *ja = JsonArray(jav);
					char name[MAX_PATH];

					for (j = 0;j < e->num_value;j++)
					{
						PackArrayElementToJsonArray(ja, p, e, j);
					}

					StrCpy(name, sizeof(name), e->name);
					StrCat(name, sizeof(name), suffix);

					JsonSet(o, name, jav);
				}
			}
		}
		else if (e->num_value == 1)
		{
			PackElementToJsonObject(o, p, e, 0);
		}
	}

	ReleaseStrList(json_group_id_list);

	return v;
}