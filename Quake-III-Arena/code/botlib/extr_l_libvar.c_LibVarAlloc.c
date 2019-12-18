#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* name; struct TYPE_5__* next; } ;
typedef  TYPE_1__ libvar_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ GetMemory (scalar_t__) ; 
 TYPE_1__* libvarlist ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

libvar_t *LibVarAlloc(char *var_name)
{
	libvar_t *v;

	v = (libvar_t *) GetMemory(sizeof(libvar_t) + strlen(var_name) + 1);
	Com_Memset(v, 0, sizeof(libvar_t));
	v->name = (char *) v + sizeof(libvar_t);
	strcpy(v->name, var_name);
	//add the variable in the list
	v->next = libvarlist;
	libvarlist = v;
	return v;
}