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
struct TYPE_4__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ symtable_rec ;
typedef  int /*<<< orphan*/  UWORD ;

/* Variables and functions */
 int SYMTABLE_USER_INITIAL_SIZE ; 
 scalar_t__ Util_malloc (int) ; 
 scalar_t__ Util_realloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  Util_strdup (char const*) ; 
 TYPE_1__* symtable_user ; 
 int symtable_user_size ; 

__attribute__((used)) static void add_user_label(const char *name, UWORD addr)
{
#define SYMTABLE_USER_INITIAL_SIZE 128
	if (symtable_user == NULL)
		symtable_user = (symtable_rec *) Util_malloc(SYMTABLE_USER_INITIAL_SIZE * sizeof(symtable_rec));
	else if (symtable_user_size >= SYMTABLE_USER_INITIAL_SIZE
	      && (symtable_user_size & (symtable_user_size - 1)) == 0) {
		/* symtable_user_size is a power of two: allocate twice as much */
		symtable_user = (symtable_rec *) Util_realloc(symtable_user,
			2 * symtable_user_size * sizeof(symtable_rec));
	}
	symtable_user[symtable_user_size].name = Util_strdup(name);
	symtable_user[symtable_user_size].addr = addr;
	symtable_user_size++;
}