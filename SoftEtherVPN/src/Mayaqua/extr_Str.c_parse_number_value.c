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
typedef  int /*<<< orphan*/  UINT64 ;
typedef  int /*<<< orphan*/  JSON_VALUE ;

/* Variables and functions */
 int /*<<< orphan*/ * JsonNewNumber (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Json_ToInt64Ex (char*,char**,int*) ; 

__attribute__((used)) static JSON_VALUE * parse_number_value(char **string) {
	char *end;
	bool error = false;
	UINT64 number = 0;
	number = Json_ToInt64Ex(*string, &end, &error);

	if (error)
	{
		return NULL;
	}
	*string = end;
	return JsonNewNumber(number);
}