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
struct TYPE_4__ {int generate_vcall_entries; scalar_t__ vbase; int /*<<< orphan*/  derived; } ;
typedef  TYPE_1__ vtbl_init_data ;
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ BINFO_VIRTUAL_P (scalar_t__) ; 
 scalar_t__ TYPE_BINFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_vcall_offset_vtbl_entries_r (scalar_t__,TYPE_1__*) ; 

__attribute__((used)) static void
build_vcall_offset_vtbl_entries (tree binfo, vtbl_init_data* vid)
{
  /* We only need these entries if this base is a virtual base.  We
     compute the indices -- but do not add to the vtable -- when
     building the main vtable for a class.  */
  if (BINFO_VIRTUAL_P (binfo) || binfo == TYPE_BINFO (vid->derived))
    {
      /* We need a vcall offset for each of the virtual functions in this
	 vtable.  For example:

	   class A { virtual void f (); };
	   class B1 : virtual public A { virtual void f (); };
	   class B2 : virtual public A { virtual void f (); };
	   class C: public B1, public B2 { virtual void f (); };

	 A C object has a primary base of B1, which has a primary base of A.  A
	 C also has a secondary base of B2, which no longer has a primary base
	 of A.  So the B2-in-C construction vtable needs a secondary vtable for
	 A, which will adjust the A* to a B2* to call f.  We have no way of
	 knowing what (or even whether) this offset will be when we define B2,
	 so we store this "vcall offset" in the A sub-vtable and look it up in
	 a "virtual thunk" for B2::f.

	 We need entries for all the functions in our primary vtable and
	 in our non-virtual bases' secondary vtables.  */
      vid->vbase = binfo;
      /* If we are just computing the vcall indices -- but do not need
	 the actual entries -- not that.  */
      if (!BINFO_VIRTUAL_P (binfo))
	vid->generate_vcall_entries = false;
      /* Now, walk through the non-virtual bases, adding vcall offsets.  */
      add_vcall_offset_vtbl_entries_r (binfo, vid);
    }
}