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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ BINFO_BASE_ACCESS (scalar_t__,unsigned int) ; 
 unsigned int BINFO_N_BASE_BINFOS (scalar_t__) ; 
 scalar_t__ CLASSTYPE_CONSTRUCTORS (scalar_t__) ; 
 scalar_t__ CLASSTYPE_DESTRUCTORS (scalar_t__) ; 
 scalar_t__ CLASSTYPE_FRIEND_CLASSES (scalar_t__) ; 
 int /*<<< orphan*/  CLASSTYPE_LAZY_COPY_CTOR (scalar_t__) ; 
 int /*<<< orphan*/  CLASSTYPE_LAZY_DEFAULT_CTOR (scalar_t__) ; 
 scalar_t__ CLASSTYPE_TEMPLATE_INSTANTIATION (scalar_t__) ; 
 int /*<<< orphan*/  DECL_ARTIFICIAL (scalar_t__) ; 
 int /*<<< orphan*/  DECL_CONSTRUCTOR_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_DESTRUCTOR_P (scalar_t__) ; 
 scalar_t__ DECL_FRIENDLIST (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_STATIC_FUNCTION_P (scalar_t__) ; 
 int /*<<< orphan*/  OPT_Wctor_dtor_privacy ; 
 scalar_t__ OVL_CURRENT (scalar_t__) ; 
 scalar_t__ OVL_NEXT (scalar_t__) ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_PRIVATE (scalar_t__) ; 
 scalar_t__ TYPE_BINFO (scalar_t__) ; 
 scalar_t__ TYPE_HAS_CONSTRUCTOR (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_HAS_INIT_REF (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MAIN_DECL (scalar_t__) ; 
 scalar_t__ TYPE_METHODS (scalar_t__) ; 
 scalar_t__ access_private_node ; 
 int /*<<< orphan*/  warn_ctor_dtor_privacy ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static void
maybe_warn_about_overly_private_class (tree t)
{
  int has_member_fn = 0;
  int has_nonprivate_method = 0;
  tree fn;

  if (!warn_ctor_dtor_privacy
      /* If the class has friends, those entities might create and
	 access instances, so we should not warn.  */
      || (CLASSTYPE_FRIEND_CLASSES (t)
	  || DECL_FRIENDLIST (TYPE_MAIN_DECL (t)))
      /* We will have warned when the template was declared; there's
	 no need to warn on every instantiation.  */
      || CLASSTYPE_TEMPLATE_INSTANTIATION (t))
    /* There's no reason to even consider warning about this
       class.  */
    return;

  /* We only issue one warning, if more than one applies, because
     otherwise, on code like:

     class A {
       // Oops - forgot `public:'
       A();
       A(const A&);
       ~A();
     };

     we warn several times about essentially the same problem.  */

  /* Check to see if all (non-constructor, non-destructor) member
     functions are private.  (Since there are no friends or
     non-private statics, we can't ever call any of the private member
     functions.)  */
  for (fn = TYPE_METHODS (t); fn; fn = TREE_CHAIN (fn))
    /* We're not interested in compiler-generated methods; they don't
       provide any way to call private members.  */
    if (!DECL_ARTIFICIAL (fn))
      {
	if (!TREE_PRIVATE (fn))
	  {
	    if (DECL_STATIC_FUNCTION_P (fn))
	      /* A non-private static member function is just like a
		 friend; it can create and invoke private member
		 functions, and be accessed without a class
		 instance.  */
	      return;

	    has_nonprivate_method = 1;
	    /* Keep searching for a static member function.  */
	  }
	else if (!DECL_CONSTRUCTOR_P (fn) && !DECL_DESTRUCTOR_P (fn))
	  has_member_fn = 1;
      }

  if (!has_nonprivate_method && has_member_fn)
    {
      /* There are no non-private methods, and there's at least one
	 private member function that isn't a constructor or
	 destructor.  (If all the private members are
	 constructors/destructors we want to use the code below that
	 issues error messages specifically referring to
	 constructors/destructors.)  */
      unsigned i;
      tree binfo = TYPE_BINFO (t);

      for (i = 0; i != BINFO_N_BASE_BINFOS (binfo); i++)
	if (BINFO_BASE_ACCESS (binfo, i) != access_private_node)
	  {
	    has_nonprivate_method = 1;
	    break;
	  }
      if (!has_nonprivate_method)
	{
	  warning (OPT_Wctor_dtor_privacy,
		   "all member functions in class %qT are private", t);
	  return;
	}
    }

  /* Even if some of the member functions are non-private, the class
     won't be useful for much if all the constructors or destructors
     are private: such an object can never be created or destroyed.  */
  fn = CLASSTYPE_DESTRUCTORS (t);
  if (fn && TREE_PRIVATE (fn))
    {
      warning (OPT_Wctor_dtor_privacy,
	       "%q#T only defines a private destructor and has no friends",
	       t);
      return;
    }

  if (TYPE_HAS_CONSTRUCTOR (t)
      /* Implicitly generated constructors are always public.  */
      && (!CLASSTYPE_LAZY_DEFAULT_CTOR (t)
	  || !CLASSTYPE_LAZY_COPY_CTOR (t)))
    {
      int nonprivate_ctor = 0;

      /* If a non-template class does not define a copy
	 constructor, one is defined for it, enabling it to avoid
	 this warning.  For a template class, this does not
	 happen, and so we would normally get a warning on:

	   template <class T> class C { private: C(); };

	 To avoid this asymmetry, we check TYPE_HAS_INIT_REF.  All
	 complete non-template or fully instantiated classes have this
	 flag set.  */
      if (!TYPE_HAS_INIT_REF (t))
	nonprivate_ctor = 1;
      else
	for (fn = CLASSTYPE_CONSTRUCTORS (t); fn; fn = OVL_NEXT (fn))
	  {
	    tree ctor = OVL_CURRENT (fn);
	    /* Ideally, we wouldn't count copy constructors (or, in
	       fact, any constructor that takes an argument of the
	       class type as a parameter) because such things cannot
	       be used to construct an instance of the class unless
	       you already have one.  But, for now at least, we're
	       more generous.  */
	    if (! TREE_PRIVATE (ctor))
	      {
		nonprivate_ctor = 1;
		break;
	      }
	  }

      if (nonprivate_ctor == 0)
	{
	  warning (OPT_Wctor_dtor_privacy,
		   "%q#T only defines private constructors and has no friends",
		   t);
	  return;
	}
    }
}