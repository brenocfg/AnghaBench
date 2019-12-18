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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {char* (* strip_name_encoding ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ DECL_COMMON (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_EXTERNAL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_INITIAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_ONE_ONLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_RTL (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_WEAK (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_PUBLIC (int /*<<< orphan*/ ) ; 
 scalar_t__ VAR_DECL ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ error_mark_node ; 
 char* first_global_object_name ; 
 char* ggc_strdup (char const*) ; 
 char* stub1 (int /*<<< orphan*/ ) ; 
 TYPE_1__ targetm ; 
 char* weak_global_object_name ; 

void
notice_global_symbol (tree decl)
{
  const char **type = &first_global_object_name;

  if (first_global_object_name
      || !TREE_PUBLIC (decl)
      || DECL_EXTERNAL (decl)
      || !DECL_NAME (decl)
      || (TREE_CODE (decl) != FUNCTION_DECL
	  && (TREE_CODE (decl) != VAR_DECL
	      || (DECL_COMMON (decl)
		  && (DECL_INITIAL (decl) == 0
		      || DECL_INITIAL (decl) == error_mark_node))))
      || !MEM_P (DECL_RTL (decl)))
    return;

  /* We win when global object is found, but it is useful to know about weak
     symbol as well so we can produce nicer unique names.  */
  if (DECL_WEAK (decl) || DECL_ONE_ONLY (decl))
    type = &weak_global_object_name;

  if (!*type)
    {
      const char *p;
      const char *name;
      rtx decl_rtl = DECL_RTL (decl);

      p = targetm.strip_name_encoding (XSTR (XEXP (decl_rtl, 0), 0));
      name = ggc_strdup (p);

      *type = name;
    }
}