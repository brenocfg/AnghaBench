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
typedef  size_t u_int ;
struct TYPE_4__ {char* name; size_t basetype; } ;
typedef  TYPE_1__ SmiType ;
typedef  int /*<<< orphan*/  SmiNode ;

/* Variables and functions */
 scalar_t__ SMI_BASETYPE_BITS ; 
 scalar_t__ SMI_BASETYPE_ENUM ; 
 scalar_t__ SMI_BASETYPE_OCTETSTRING ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_enum (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 TYPE_1__* smiGetNodeType (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char** type_map ; 
 char** type_names ; 

__attribute__((used)) static void
print_type(SmiNode *n)
{
	SmiType *type;
	u_int m;

	type = smiGetNodeType(n);
	assert(type != NULL);

	if (type->name != NULL) {
		for (m = 0; type_map[m] != NULL; m += 2)
			if (strcmp(type_map[m], type->name) == 0) {
				printf("%s", type_map[m + 1]);
				return;
			}
	}
	printf("%s", type_names[type->basetype]);

	if (type->basetype == SMI_BASETYPE_ENUM ||
	    type->basetype == SMI_BASETYPE_BITS)
		print_enum(type);

	else if (type->basetype == SMI_BASETYPE_OCTETSTRING &&
	    type->name != NULL)
		printf(" | %s", type->name);
}