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

/* Variables and functions */
 char* ID_OPHANDLER_NAME ; 
 int /*<<< orphan*/  MAX_NAME_LENGTH ; 
 int /*<<< orphan*/  MAX_SPEC_EA_LENGTH ; 
 int /*<<< orphan*/  MAX_SPEC_PROC_LENGTH ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  check_strcncpy (char*,char*,char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_spaces (char*) ; 
 scalar_t__ strlen (char*) ; 
 char* strstr (char*,char*) ; 

int extract_opcode_info(char* src, char* name, int* size, char* spec_proc, char* spec_ea)
{
	char* ptr = strstr(src, ID_OPHANDLER_NAME);

	if(ptr == NULL)
		return 0;

	ptr += strlen(ID_OPHANDLER_NAME) + 1;

	ptr += check_strcncpy(name, ptr, ',', MAX_NAME_LENGTH);
	if(*ptr != ',') return 0;
	ptr++;
	ptr += skip_spaces(ptr);

	*size = atoi(ptr);
	ptr = strstr(ptr, ",");
	if(ptr == NULL) return 0;
    ptr++;
	ptr += skip_spaces(ptr);

	ptr += check_strcncpy(spec_proc, ptr, ',', MAX_SPEC_PROC_LENGTH);
	if(*ptr != ',') return 0;
	ptr++;
	ptr += skip_spaces(ptr);

	ptr += check_strcncpy(spec_ea, ptr, ')', MAX_SPEC_EA_LENGTH);
	if(*ptr != ')') return 0;
	ptr++;
	ptr += skip_spaces(ptr);

	return 1;
}