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
typedef  int /*<<< orphan*/  cp_response ;

/* Variables and functions */
 int /*<<< orphan*/  cpcmd (char*,char*,int,int /*<<< orphan*/ *) ; 
 char* strnchr (char*,int,char) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int strnlen (char*,int) ; 

__attribute__((used)) static int vmlogrdr_get_recording_class_AB(void)
{
	char cp_command[]="QUERY COMMAND RECORDING ";
	char cp_response[80];
	char *tail;
	int len,i;

	cpcmd(cp_command, cp_response, sizeof(cp_response), NULL);
	len = strnlen(cp_response,sizeof(cp_response));
	// now the parsing
	tail=strnchr(cp_response,len,'=');
	if (!tail)
		return 0;
	tail++;
	if (!strncmp("ANY",tail,3))
		return 1;
	if (!strncmp("NONE",tail,4))
		return 0;
	/*
	 * expect comma separated list of classes here, if one of them
	 * is A or B return 1 otherwise 0
	 */
        for (i=tail-cp_response; i<len; i++)
		if ( cp_response[i]=='A' || cp_response[i]=='B' )
			return 1;
	return 0;
}