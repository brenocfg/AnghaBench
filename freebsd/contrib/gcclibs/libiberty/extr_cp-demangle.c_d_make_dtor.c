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
struct demangle_component {int dummy; } ;
struct d_info {int dummy; } ;
typedef  enum gnu_v3_dtor_kinds { ____Placeholder_gnu_v3_dtor_kinds } gnu_v3_dtor_kinds ;

/* Variables and functions */
 int /*<<< orphan*/  cplus_demangle_fill_dtor (struct demangle_component*,int,struct demangle_component*) ; 
 struct demangle_component* d_make_empty (struct d_info*) ; 

__attribute__((used)) static struct demangle_component *
d_make_dtor (struct d_info *di, enum gnu_v3_dtor_kinds kind,
             struct demangle_component *name)
{
  struct demangle_component *p;

  p = d_make_empty (di);
  if (! cplus_demangle_fill_dtor (p, kind, name))
    return NULL;
  return p;
}