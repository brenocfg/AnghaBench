#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; } ;
typedef  TYPE_1__ Path ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  int /*<<< orphan*/  Lst ;

/* Variables and functions */
 int /*<<< orphan*/  Lst_Close (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Lst_Next (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STR_ADDSPACE ; 
 scalar_t__ SUCCESS ; 
 char* bmake_strdup (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* str_concat (char const*,char*,int /*<<< orphan*/ ) ; 

char *
Dir_MakeFlags(const char *flag, Lst path)
{
    char	  *str;	  /* the string which will be returned */
    char	  *s1, *s2;/* the current directory preceded by 'flag' */
    LstNode	  ln;	  /* the node of the current directory */
    Path	  *p;	  /* the structure describing the current directory */

    str = bmake_strdup("");

    if (Lst_Open(path) == SUCCESS) {
	while ((ln = Lst_Next(path)) != NULL) {
	    p = (Path *)Lst_Datum(ln);
	    s2 = str_concat(flag, p->name, 0);
	    str = str_concat(s1 = str, s2, STR_ADDSPACE);
	    free(s1);
	    free(s2);
	}
	Lst_Close(path);
    }

    return (str);
}