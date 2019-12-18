#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int num_strings; int max_strings; char** strings; } ;
typedef  TYPE_1__ STRING_VEC_T ;

/* Variables and functions */
 int /*<<< orphan*/  fatal_error (char*) ; 
 char* malloc (int) ; 
 char** realloc (char**,int) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

char *string_vec_add(STRING_VEC_T *vec, const char *str, int len)
{
    char *copy;
    if (vec->num_strings == vec->max_strings)
    {
	if (vec->max_strings)
	    vec->max_strings *= 2;
	else
	    vec->max_strings = 16;
	vec->strings = realloc(vec->strings, vec->max_strings * sizeof(const char *));
	if (!vec->strings)
	    fatal_error("Out of memory");
    }

    if (len)
    {
	copy = malloc(len + 1);
	strncpy(copy, str, len);
	copy[len] = '\0';
    }
    else
       copy = strdup(str);

    if (!copy)
	fatal_error("Out of memory");

    vec->strings[vec->num_strings++] = copy;

    return copy;
}