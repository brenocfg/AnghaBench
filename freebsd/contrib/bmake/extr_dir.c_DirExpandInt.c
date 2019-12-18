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
typedef  int /*<<< orphan*/  Path ;
typedef  int /*<<< orphan*/ * LstNode ;
typedef  int /*<<< orphan*/  Lst ;

/* Variables and functions */
 int /*<<< orphan*/  DirMatchFiles (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lst_Close (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Datum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Lst_Next (int /*<<< orphan*/ ) ; 
 scalar_t__ Lst_Open (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCESS ; 

__attribute__((used)) static void
DirExpandInt(const char *word, Lst path, Lst expansions)
{
    LstNode 	  ln;	    	/* Current node */
    Path	  *p;	    	/* Directory in the node */

    if (Lst_Open(path) == SUCCESS) {
	while ((ln = Lst_Next(path)) != NULL) {
	    p = (Path *)Lst_Datum(ln);
	    DirMatchFiles(word, p, expansions);
	}
	Lst_Close(path);
    }
}