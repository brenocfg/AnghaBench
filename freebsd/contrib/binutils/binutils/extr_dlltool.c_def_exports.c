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
struct export {char const* name; char const* internal_name; char const* import_name; int ordinal; int constant; int noname; int private; int data; scalar_t__ forward; struct export* next; } ;

/* Variables and functions */
 struct export* d_exports ; 
 scalar_t__ d_nforwards ; 
 int /*<<< orphan*/  d_nfuncs ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 
 scalar_t__ xmalloc (int) ; 

void
def_exports (const char *name, const char *internal_name, int ordinal,
	     int noname, int constant, int data, int private)
{
  struct export *p = (struct export *) xmalloc (sizeof (*p));

  p->name = name;
  p->internal_name = internal_name ? internal_name : name;
  p->import_name = name;
  p->ordinal = ordinal;
  p->constant = constant;
  p->noname = noname;
  p->private = private;
  p->data = data;
  p->next = d_exports;
  d_exports = p;
  d_nfuncs++;

  if ((internal_name != NULL)
      && (strchr (internal_name, '.') != NULL))
    p->forward = ++d_nforwards;
  else
    p->forward = 0; /* no forward */
}