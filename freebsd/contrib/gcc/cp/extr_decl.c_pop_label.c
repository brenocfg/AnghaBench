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
typedef  int /*<<< orphan*/  tree ;
struct TYPE_4__ {scalar_t__ line; int /*<<< orphan*/  file; } ;
typedef  TYPE_1__ location_t ;

/* Variables and functions */
 scalar_t__ DECL_INITIAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  OPT_Wunused_label ; 
 int /*<<< orphan*/  SET_IDENTIFIER_LABEL_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_USED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  define_label (TYPE_1__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_filename ; 
 TYPE_1__ input_location ; 
 int /*<<< orphan*/  processing_template_decl ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pop_label (tree label, tree old_value)
{
  if (!processing_template_decl)
    {
      if (DECL_INITIAL (label) == NULL_TREE)
	{
	  location_t location;

	  error ("label %q+D used but not defined", label);
#ifdef USE_MAPPED_LOCATION
	  location = input_location; /* FIXME want (input_filename, (line)0) */
#else
	  location.file = input_filename;
	  location.line = 0;
#endif
	  /* Avoid crashing later.  */
	  define_label (location, DECL_NAME (label));
	}
      else if (!TREE_USED (label))
	warning (OPT_Wunused_label, "label %q+D defined but not used", label);
    }

  SET_IDENTIFIER_LABEL_VALUE (DECL_NAME (label), old_value);
}