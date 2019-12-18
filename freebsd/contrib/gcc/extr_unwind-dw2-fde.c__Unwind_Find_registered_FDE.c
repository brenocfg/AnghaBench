#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int encoding; scalar_t__ mixed_encoding; } ;
struct TYPE_8__ {TYPE_1__ b; } ;
struct object {void* pc_begin; TYPE_2__ s; int /*<<< orphan*/  dbase; int /*<<< orphan*/  tbase; struct object* next; } ;
struct dwarf_eh_bases {void* func; int /*<<< orphan*/  dbase; int /*<<< orphan*/  tbase; } ;
struct TYPE_9__ {int /*<<< orphan*/  pc_begin; } ;
typedef  TYPE_3__ fde ;
typedef  scalar_t__ _Unwind_Ptr ;

/* Variables and functions */
 int /*<<< orphan*/  __gthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __gthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  base_from_object (int,struct object*) ; 
 int get_fde_encoding (TYPE_3__ const*) ; 
 int /*<<< orphan*/  init_object_mutex_once () ; 
 int /*<<< orphan*/  object_mutex ; 
 int /*<<< orphan*/  read_encoded_value_with_base (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_3__* search_object (struct object*,void*) ; 
 struct object* seen_objects ; 
 struct object* unseen_objects ; 

const fde *
_Unwind_Find_FDE (void *pc, struct dwarf_eh_bases *bases)
{
  struct object *ob;
  const fde *f = NULL;

  init_object_mutex_once ();
  __gthread_mutex_lock (&object_mutex);

  /* Linear search through the classified objects, to find the one
     containing the pc.  Note that pc_begin is sorted descending, and
     we expect objects to be non-overlapping.  */
  for (ob = seen_objects; ob; ob = ob->next)
    if (pc >= ob->pc_begin)
      {
	f = search_object (ob, pc);
	if (f)
	  goto fini;
	break;
      }

  /* Classify and search the objects we've not yet processed.  */
  while ((ob = unseen_objects))
    {
      struct object **p;

      unseen_objects = ob->next;
      f = search_object (ob, pc);

      /* Insert the object into the classified list.  */
      for (p = &seen_objects; *p ; p = &(*p)->next)
	if ((*p)->pc_begin < ob->pc_begin)
	  break;
      ob->next = *p;
      *p = ob;

      if (f)
	goto fini;
    }

 fini:
  __gthread_mutex_unlock (&object_mutex);

  if (f)
    {
      int encoding;
      _Unwind_Ptr func;

      bases->tbase = ob->tbase;
      bases->dbase = ob->dbase;

      encoding = ob->s.b.encoding;
      if (ob->s.b.mixed_encoding)
	encoding = get_fde_encoding (f);
      read_encoded_value_with_base (encoding, base_from_object (encoding, ob),
				    f->pc_begin, &func);
      bases->func = (void *) func;
    }

  return f;
}