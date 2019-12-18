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
struct queue_elem {int /*<<< orphan*/  lineno; int /*<<< orphan*/  data; struct queue_elem* next; } ;
struct TYPE_2__ {int /*<<< orphan*/  lineno; } ;

/* Variables and functions */
#define  CONST 129 
#define  CONST_STRING 128 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 char const* XSTR (int /*<<< orphan*/ ,int) ; 
 struct queue_elem* define_attr_queue ; 
 TYPE_1__* define_cond_exec_queue ; 
 int errors ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  message_with_line (int /*<<< orphan*/ ,char*,...) ; 
 int predicable_default ; 
 char* predicable_false ; 
 char* predicable_true ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* xstrdup (char const*) ; 

__attribute__((used)) static void
identify_predicable_attribute (void)
{
  struct queue_elem *elem;
  char *p_true, *p_false;
  const char *value;

  /* Look for the DEFINE_ATTR for `predicable', which must exist.  */
  for (elem = define_attr_queue; elem ; elem = elem->next)
    if (strcmp (XSTR (elem->data, 0), "predicable") == 0)
      goto found;

  message_with_line (define_cond_exec_queue->lineno,
		     "attribute `predicable' not defined");
  errors = 1;
  return;

 found:
  value = XSTR (elem->data, 1);
  p_false = xstrdup (value);
  p_true = strchr (p_false, ',');
  if (p_true == NULL || strchr (++p_true, ',') != NULL)
    {
      message_with_line (elem->lineno,
			 "attribute `predicable' is not a boolean");
      errors = 1;
      if (p_false)
        free (p_false);
      return;
    }
  p_true[-1] = '\0';

  predicable_true = p_true;
  predicable_false = p_false;

  switch (GET_CODE (XEXP (elem->data, 2)))
    {
    case CONST_STRING:
      value = XSTR (XEXP (elem->data, 2), 0);
      break;

    case CONST:
      message_with_line (elem->lineno,
			 "attribute `predicable' cannot be const");
      errors = 1;
      if (p_false)
	free (p_false);
      return;

    default:
      message_with_line (elem->lineno,
			 "attribute `predicable' must have a constant default");
      errors = 1;
      if (p_false)
	free (p_false);
      return;
    }

  if (strcmp (value, p_true) == 0)
    predicable_default = 1;
  else if (strcmp (value, p_false) == 0)
    predicable_default = 0;
  else
    {
      message_with_line (elem->lineno,
			 "unknown value `%s' for `predicable' attribute",
			 value);
      errors = 1;
      if (p_false)
	free (p_false);
    }
}