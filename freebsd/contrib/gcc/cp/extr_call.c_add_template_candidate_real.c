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
typedef  int /*<<< orphan*/  unification_kind_t ;
typedef  scalar_t__ tree ;
struct z_candidate {int /*<<< orphan*/  template_decl; } ;

/* Variables and functions */
 scalar_t__ CLASSTYPE_VBASECLASSES (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_BASE_CONSTRUCTOR_P (scalar_t__) ; 
 scalar_t__ DECL_CONSTRUCTOR_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_CONTEXT (scalar_t__) ; 
 scalar_t__ DECL_MAYBE_IN_CHARGE_CONSTRUCTOR_P (scalar_t__) ; 
 scalar_t__ DECL_NONSTATIC_MEMBER_FUNCTION_P (scalar_t__) ; 
 int DECL_NTPARMS (scalar_t__) ; 
 int /*<<< orphan*/  DECL_TEMPLATE_INFO (scalar_t__) ; 
 scalar_t__ DECL_TI_TEMPLATE (scalar_t__) ; 
 scalar_t__ FUNCTION_FIRST_USER_PARMTYPE (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int /*<<< orphan*/  TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 struct z_candidate* add_conv_candidate (struct z_candidate**,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 struct z_candidate* add_function_candidate (struct z_candidate**,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 scalar_t__ error_mark_node ; 
 int fn_type_unification (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ instantiate_template (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int list_length (scalar_t__) ; 
 scalar_t__ make_tree_vec (int) ; 
 scalar_t__ same_type_p (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tf_none ; 
 int /*<<< orphan*/  tree_cons (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct z_candidate*
add_template_candidate_real (struct z_candidate **candidates, tree tmpl,
			     tree ctype, tree explicit_targs, tree arglist,
			     tree return_type, tree access_path,
			     tree conversion_path, int flags, tree obj,
			     unification_kind_t strict)
{
  int ntparms = DECL_NTPARMS (tmpl);
  tree targs = make_tree_vec (ntparms);
  tree args_without_in_chrg = arglist;
  struct z_candidate *cand;
  int i;
  tree fn;

  /* We don't do deduction on the in-charge parameter, the VTT
     parameter or 'this'.  */
  if (DECL_NONSTATIC_MEMBER_FUNCTION_P (tmpl))
    args_without_in_chrg = TREE_CHAIN (args_without_in_chrg);

  if ((DECL_MAYBE_IN_CHARGE_CONSTRUCTOR_P (tmpl)
       || DECL_BASE_CONSTRUCTOR_P (tmpl))
      && CLASSTYPE_VBASECLASSES (DECL_CONTEXT (tmpl)))
    args_without_in_chrg = TREE_CHAIN (args_without_in_chrg);

  i = fn_type_unification (tmpl, explicit_targs, targs,
			   args_without_in_chrg,
			   return_type, strict, flags);

  if (i != 0)
    return NULL;

  fn = instantiate_template (tmpl, targs, tf_none);
  if (fn == error_mark_node)
    return NULL;

  /* In [class.copy]:

       A member function template is never instantiated to perform the
       copy of a class object to an object of its class type.

     It's a little unclear what this means; the standard explicitly
     does allow a template to be used to copy a class.  For example,
     in:

       struct A {
	 A(A&);
	 template <class T> A(const T&);
       };
       const A f ();
       void g () { A a (f ()); }

     the member template will be used to make the copy.  The section
     quoted above appears in the paragraph that forbids constructors
     whose only parameter is (a possibly cv-qualified variant of) the
     class type, and a logical interpretation is that the intent was
     to forbid the instantiation of member templates which would then
     have that form.  */
  if (DECL_CONSTRUCTOR_P (fn) && list_length (arglist) == 2)
    {
      tree arg_types = FUNCTION_FIRST_USER_PARMTYPE (fn);
      if (arg_types && same_type_p (TYPE_MAIN_VARIANT (TREE_VALUE (arg_types)),
				    ctype))
	return NULL;
    }

  if (obj != NULL_TREE)
    /* Aha, this is a conversion function.  */
    cand = add_conv_candidate (candidates, fn, obj, access_path,
			       conversion_path, arglist);
  else
    cand = add_function_candidate (candidates, fn, ctype,
				   arglist, access_path,
				   conversion_path, flags);
  if (DECL_TI_TEMPLATE (fn) != tmpl)
    /* This situation can occur if a member template of a template
       class is specialized.  Then, instantiate_template might return
       an instantiation of the specialization, in which case the
       DECL_TI_TEMPLATE field will point at the original
       specialization.  For example:

	 template <class T> struct S { template <class U> void f(U);
				       template <> void f(int) {}; };
	 S<double> sd;
	 sd.f(3);

       Here, TMPL will be template <class U> S<double>::f(U).
       And, instantiate template will give us the specialization
       template <> S<double>::f(int).  But, the DECL_TI_TEMPLATE field
       for this will point at template <class T> template <> S<T>::f(int),
       so that we can find the definition.  For the purposes of
       overload resolution, however, we want the original TMPL.  */
    cand->template_decl = tree_cons (tmpl, targs, NULL_TREE);
  else
    cand->template_decl = DECL_TEMPLATE_INFO (fn);

  return cand;
}