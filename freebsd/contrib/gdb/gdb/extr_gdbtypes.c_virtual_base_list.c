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
struct vbase {struct vbase* next; struct type* vbasetype; } ;
struct type {int dummy; } ;

/* Variables and functions */
 struct vbase* current_vbase_list ; 
 int /*<<< orphan*/  virtual_base_list_aux (struct type*) ; 
 int /*<<< orphan*/  xfree (struct vbase*) ; 
 scalar_t__ xmalloc (int) ; 

struct type **
virtual_base_list (struct type *dclass)
{
  struct vbase *tmp_vbase;
  struct vbase *tmp_vbase_2;
  int i;
  int count;
  struct type **vbase_array;

  current_vbase_list = NULL;
  virtual_base_list_aux (dclass);

  for (i = 0, tmp_vbase = current_vbase_list; tmp_vbase != NULL; i++, tmp_vbase = tmp_vbase->next)
    /* no body */ ;

  count = i;

  vbase_array = (struct type **) xmalloc ((count + 1) * sizeof (struct type *));

  for (i = count - 1, tmp_vbase = current_vbase_list; i >= 0; i--, tmp_vbase = tmp_vbase->next)
    vbase_array[i] = tmp_vbase->vbasetype;

  /* Get rid of constructed chain */
  tmp_vbase_2 = tmp_vbase = current_vbase_list;
  while (tmp_vbase)
    {
      tmp_vbase = tmp_vbase->next;
      xfree (tmp_vbase_2);
      tmp_vbase_2 = tmp_vbase;
    }

  vbase_array[count] = NULL;
  return vbase_array;
}