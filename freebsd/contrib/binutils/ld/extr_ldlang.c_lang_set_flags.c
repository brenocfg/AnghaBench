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
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  not_flags; } ;
typedef  TYPE_1__ lang_memory_region_type ;
typedef  int /*<<< orphan*/  flagword ;

/* Variables and functions */
 int /*<<< orphan*/  SEC_ALLOC ; 
 int /*<<< orphan*/  SEC_CODE ; 
 int /*<<< orphan*/  SEC_DATA ; 
 int /*<<< orphan*/  SEC_LOAD ; 
 int /*<<< orphan*/  SEC_READONLY ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  einfo (int /*<<< orphan*/ ) ; 

void
lang_set_flags (lang_memory_region_type *ptr, const char *flags, int invert)
{
  flagword *ptr_flags;

  ptr_flags = invert ? &ptr->not_flags : &ptr->flags;
  while (*flags)
    {
      switch (*flags)
	{
	case 'A': case 'a':
	  *ptr_flags |= SEC_ALLOC;
	  break;

	case 'R': case 'r':
	  *ptr_flags |= SEC_READONLY;
	  break;

	case 'W': case 'w':
	  *ptr_flags |= SEC_DATA;
	  break;

	case 'X': case 'x':
	  *ptr_flags |= SEC_CODE;
	  break;

	case 'L': case 'l':
	case 'I': case 'i':
	  *ptr_flags |= SEC_LOAD;
	  break;

	default:
	  einfo (_("%P%F: invalid syntax in flags\n"));
	  break;
	}
      flags++;
    }
}