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
struct TYPE_2__ {int /*<<< orphan*/ * substitutions; } ;

/* Variables and functions */
 TYPE_1__ G ; 
 size_t SUBID_ALLOCATOR ; 
 size_t SUBID_BASIC_IOSTREAM ; 
 size_t SUBID_BASIC_ISTREAM ; 
 size_t SUBID_BASIC_OSTREAM ; 
 size_t SUBID_BASIC_STRING ; 
 size_t SUBID_CHAR_TRAITS ; 
 int /*<<< orphan*/  gcc_obstack_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_identifier (char*) ; 
 int /*<<< orphan*/  name_base ; 
 int /*<<< orphan*/  name_obstack ; 
 int /*<<< orphan*/  obstack_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * subst_identifiers ; 

void
init_mangle (void)
{
  gcc_obstack_init (&name_obstack);
  name_base = obstack_alloc (&name_obstack, 0);
  G.substitutions = NULL;

  /* Cache these identifiers for quick comparison when checking for
     standard substitutions.  */
  subst_identifiers[SUBID_ALLOCATOR] = get_identifier ("allocator");
  subst_identifiers[SUBID_BASIC_STRING] = get_identifier ("basic_string");
  subst_identifiers[SUBID_CHAR_TRAITS] = get_identifier ("char_traits");
  subst_identifiers[SUBID_BASIC_ISTREAM] = get_identifier ("basic_istream");
  subst_identifiers[SUBID_BASIC_OSTREAM] = get_identifier ("basic_ostream");
  subst_identifiers[SUBID_BASIC_IOSTREAM] = get_identifier ("basic_iostream");
}