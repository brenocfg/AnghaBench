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
struct TYPE_5__ {struct TYPE_5__* link; int /*<<< orphan*/ * name; } ;
typedef  int /*<<< orphan*/  Char ;
typedef  TYPE_1__ Cell ;

/* Variables and functions */
 TYPE_1__* mkCell () ; 
 scalar_t__ myMalloc (scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

__attribute__((used)) static 
Cell *snocString ( Cell *root, Char *name )
{
   if (root == NULL) {
      Cell *tmp = mkCell();
      tmp->name = (Char*) myMalloc ( 5 + strlen(name) );
      strcpy ( tmp->name, name );
      return tmp;
   } else {
      Cell *tmp = root;
      while (tmp->link != NULL) tmp = tmp->link;
      tmp->link = snocString ( tmp->link, name );
      return root;
   }
}