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
struct vbase {struct vbase* next; } ;
struct type {int dummy; } ;

/* Variables and functions */
 struct vbase* current_vbase_list ; 
 int /*<<< orphan*/  virtual_base_list_aux (struct type*) ; 

int
virtual_base_list_length (struct type *dclass)
{
  int i;
  struct vbase *tmp_vbase;

  current_vbase_list = NULL;
  virtual_base_list_aux (dclass);

  for (i = 0, tmp_vbase = current_vbase_list; tmp_vbase != NULL; i++, tmp_vbase = tmp_vbase->next)
    /* no body */ ;
  return i;
}