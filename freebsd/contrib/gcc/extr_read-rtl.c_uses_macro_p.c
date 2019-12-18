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
struct mapping {scalar_t__ index; struct macro_group* group; } ;
struct macro_group {scalar_t__ num_builtins; scalar_t__ (* uses_macro_p ) (int /*<<< orphan*/ ,scalar_t__) ;} ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  BELLWETHER_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVEC (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool
uses_macro_p (rtx x, struct mapping *macro)
{
  struct macro_group *group;
  const char *format_ptr;
  int i, j;

  if (x == 0)
    return false;

  group = macro->group;
  if (group->uses_macro_p (x, macro->index + group->num_builtins))
    return true;

  format_ptr = GET_RTX_FORMAT (BELLWETHER_CODE (GET_CODE (x)));
  for (i = 0; format_ptr[i] != 0; i++)
    switch (format_ptr[i])
      {
      case 'e':
	if (uses_macro_p (XEXP (x, i), macro))
	  return true;
	break;

      case 'V':
      case 'E':
	if (XVEC (x, i))
	  for (j = 0; j < XVECLEN (x, i); j++)
	    if (uses_macro_p (XVECEXP (x, i, j), macro))
	      return true;
	break;

      default:
	break;
      }
  return false;
}