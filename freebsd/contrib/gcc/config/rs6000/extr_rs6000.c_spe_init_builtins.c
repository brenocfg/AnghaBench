#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct builtin_description {size_t icode; char* name; int /*<<< orphan*/  code; int /*<<< orphan*/  mask; } ;
struct TYPE_8__ {TYPE_2__* operand; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* pushdecl ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_7__ {TYPE_1__ decls; } ;
struct TYPE_6__ {int mode; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVABS ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVADDW ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVCMPEQ ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVFSTSTLT ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLDD ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLDDX ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLDH ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLDHX ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLDW ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLDWX ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLHHESPLAT ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLHHESPLATX ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLHHOSSPLAT ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLHHOSSPLATX ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLHHOUSPLAT ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLHHOUSPLATX ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLWHE ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLWHEX ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLWHOS ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLWHOSX ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLWHOU ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLWHOUX ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLWHSPLAT ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLWHSPLATX ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLWWSPLAT ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVLWWSPLATX ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVSEL_CMPGTS ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVSEL_FSTSTEQ ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVSPLATFI ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVSPLATI ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVSTDD ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVSTDDX ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVSTDH ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVSTDHX ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVSTDW ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVSTDWX ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVSTWHE ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVSTWHEX ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVSTWHO ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVSTWHOX ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVSTWWE ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVSTWWEX ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVSTWWO ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVSTWWOX ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVSUBFUSIAAW ; 
 int /*<<< orphan*/  SPE_BUILTIN_EVXOR ; 
 int /*<<< orphan*/  SPE_BUILTIN_MFSPEFSCR ; 
 int /*<<< orphan*/  SPE_BUILTIN_MTSPEFSCR ; 
 int /*<<< orphan*/  TYPE_DECL ; 
#define  V2SFmode 129 
#define  V2SImode 128 
 scalar_t__ bdesc_1arg ; 
 scalar_t__ bdesc_2arg ; 
 scalar_t__ bdesc_spe_evsel ; 
 scalar_t__ bdesc_spe_predicates ; 
 int /*<<< orphan*/  build_decl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_function_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_pointer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  char_type_node ; 
 int /*<<< orphan*/  def_builtin (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_mask_for_builtins (struct builtin_description*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  get_identifier (char*) ; 
 TYPE_4__* insn_data ; 
 int /*<<< orphan*/  integer_type_node ; 
 TYPE_3__ lang_hooks ; 
 int /*<<< orphan*/  opaque_V2SF_type_node ; 
 int /*<<< orphan*/  opaque_V2SI_type_node ; 
 int /*<<< orphan*/  opaque_p_V2SI_type_node ; 
 int /*<<< orphan*/  short_unsigned_type_node ; 
 int /*<<< orphan*/  signed_char_type_node ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_flags ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unsigned_type_node ; 
 int /*<<< orphan*/  void_list_node ; 
 int /*<<< orphan*/  void_type_node ; 

__attribute__((used)) static void
spe_init_builtins (void)
{
  tree endlink = void_list_node;
  tree puint_type_node = build_pointer_type (unsigned_type_node);
  tree pushort_type_node = build_pointer_type (short_unsigned_type_node);
  struct builtin_description *d;
  size_t i;

  tree v2si_ftype_4_v2si
    = build_function_type
    (opaque_V2SI_type_node,
     tree_cons (NULL_TREE, opaque_V2SI_type_node,
		tree_cons (NULL_TREE, opaque_V2SI_type_node,
			   tree_cons (NULL_TREE, opaque_V2SI_type_node,
				      tree_cons (NULL_TREE, opaque_V2SI_type_node,
						 endlink)))));

  tree v2sf_ftype_4_v2sf
    = build_function_type
    (opaque_V2SF_type_node,
     tree_cons (NULL_TREE, opaque_V2SF_type_node,
		tree_cons (NULL_TREE, opaque_V2SF_type_node,
			   tree_cons (NULL_TREE, opaque_V2SF_type_node,
				      tree_cons (NULL_TREE, opaque_V2SF_type_node,
						 endlink)))));

  tree int_ftype_int_v2si_v2si
    = build_function_type
    (integer_type_node,
     tree_cons (NULL_TREE, integer_type_node,
		tree_cons (NULL_TREE, opaque_V2SI_type_node,
			   tree_cons (NULL_TREE, opaque_V2SI_type_node,
				      endlink))));

  tree int_ftype_int_v2sf_v2sf
    = build_function_type
    (integer_type_node,
     tree_cons (NULL_TREE, integer_type_node,
		tree_cons (NULL_TREE, opaque_V2SF_type_node,
			   tree_cons (NULL_TREE, opaque_V2SF_type_node,
				      endlink))));

  tree void_ftype_v2si_puint_int
    = build_function_type (void_type_node,
			   tree_cons (NULL_TREE, opaque_V2SI_type_node,
				      tree_cons (NULL_TREE, puint_type_node,
						 tree_cons (NULL_TREE,
							    integer_type_node,
							    endlink))));

  tree void_ftype_v2si_puint_char
    = build_function_type (void_type_node,
			   tree_cons (NULL_TREE, opaque_V2SI_type_node,
				      tree_cons (NULL_TREE, puint_type_node,
						 tree_cons (NULL_TREE,
							    char_type_node,
							    endlink))));

  tree void_ftype_v2si_pv2si_int
    = build_function_type (void_type_node,
			   tree_cons (NULL_TREE, opaque_V2SI_type_node,
				      tree_cons (NULL_TREE, opaque_p_V2SI_type_node,
						 tree_cons (NULL_TREE,
							    integer_type_node,
							    endlink))));

  tree void_ftype_v2si_pv2si_char
    = build_function_type (void_type_node,
			   tree_cons (NULL_TREE, opaque_V2SI_type_node,
				      tree_cons (NULL_TREE, opaque_p_V2SI_type_node,
						 tree_cons (NULL_TREE,
							    char_type_node,
							    endlink))));

  tree void_ftype_int
    = build_function_type (void_type_node,
			   tree_cons (NULL_TREE, integer_type_node, endlink));

  tree int_ftype_void
    = build_function_type (integer_type_node, endlink);

  tree v2si_ftype_pv2si_int
    = build_function_type (opaque_V2SI_type_node,
			   tree_cons (NULL_TREE, opaque_p_V2SI_type_node,
				      tree_cons (NULL_TREE, integer_type_node,
						 endlink)));

  tree v2si_ftype_puint_int
    = build_function_type (opaque_V2SI_type_node,
			   tree_cons (NULL_TREE, puint_type_node,
				      tree_cons (NULL_TREE, integer_type_node,
						 endlink)));

  tree v2si_ftype_pushort_int
    = build_function_type (opaque_V2SI_type_node,
			   tree_cons (NULL_TREE, pushort_type_node,
				      tree_cons (NULL_TREE, integer_type_node,
						 endlink)));

  tree v2si_ftype_signed_char
    = build_function_type (opaque_V2SI_type_node,
			   tree_cons (NULL_TREE, signed_char_type_node,
				      endlink));

  /* The initialization of the simple binary and unary builtins is
     done in rs6000_common_init_builtins, but we have to enable the
     mask bits here manually because we have run out of `target_flags'
     bits.  We really need to redesign this mask business.  */

  enable_mask_for_builtins ((struct builtin_description *) bdesc_2arg,
			    ARRAY_SIZE (bdesc_2arg),
			    SPE_BUILTIN_EVADDW,
			    SPE_BUILTIN_EVXOR);
  enable_mask_for_builtins ((struct builtin_description *) bdesc_1arg,
			    ARRAY_SIZE (bdesc_1arg),
			    SPE_BUILTIN_EVABS,
			    SPE_BUILTIN_EVSUBFUSIAAW);
  enable_mask_for_builtins ((struct builtin_description *) bdesc_spe_predicates,
			    ARRAY_SIZE (bdesc_spe_predicates),
			    SPE_BUILTIN_EVCMPEQ,
			    SPE_BUILTIN_EVFSTSTLT);
  enable_mask_for_builtins ((struct builtin_description *) bdesc_spe_evsel,
			    ARRAY_SIZE (bdesc_spe_evsel),
			    SPE_BUILTIN_EVSEL_CMPGTS,
			    SPE_BUILTIN_EVSEL_FSTSTEQ);

  (*lang_hooks.decls.pushdecl)
    (build_decl (TYPE_DECL, get_identifier ("__ev64_opaque__"),
		 opaque_V2SI_type_node));

  /* Initialize irregular SPE builtins.  */

  def_builtin (target_flags, "__builtin_spe_mtspefscr", void_ftype_int, SPE_BUILTIN_MTSPEFSCR);
  def_builtin (target_flags, "__builtin_spe_mfspefscr", int_ftype_void, SPE_BUILTIN_MFSPEFSCR);
  def_builtin (target_flags, "__builtin_spe_evstddx", void_ftype_v2si_pv2si_int, SPE_BUILTIN_EVSTDDX);
  def_builtin (target_flags, "__builtin_spe_evstdhx", void_ftype_v2si_pv2si_int, SPE_BUILTIN_EVSTDHX);
  def_builtin (target_flags, "__builtin_spe_evstdwx", void_ftype_v2si_pv2si_int, SPE_BUILTIN_EVSTDWX);
  def_builtin (target_flags, "__builtin_spe_evstwhex", void_ftype_v2si_puint_int, SPE_BUILTIN_EVSTWHEX);
  def_builtin (target_flags, "__builtin_spe_evstwhox", void_ftype_v2si_puint_int, SPE_BUILTIN_EVSTWHOX);
  def_builtin (target_flags, "__builtin_spe_evstwwex", void_ftype_v2si_puint_int, SPE_BUILTIN_EVSTWWEX);
  def_builtin (target_flags, "__builtin_spe_evstwwox", void_ftype_v2si_puint_int, SPE_BUILTIN_EVSTWWOX);
  def_builtin (target_flags, "__builtin_spe_evstdd", void_ftype_v2si_pv2si_char, SPE_BUILTIN_EVSTDD);
  def_builtin (target_flags, "__builtin_spe_evstdh", void_ftype_v2si_pv2si_char, SPE_BUILTIN_EVSTDH);
  def_builtin (target_flags, "__builtin_spe_evstdw", void_ftype_v2si_pv2si_char, SPE_BUILTIN_EVSTDW);
  def_builtin (target_flags, "__builtin_spe_evstwhe", void_ftype_v2si_puint_char, SPE_BUILTIN_EVSTWHE);
  def_builtin (target_flags, "__builtin_spe_evstwho", void_ftype_v2si_puint_char, SPE_BUILTIN_EVSTWHO);
  def_builtin (target_flags, "__builtin_spe_evstwwe", void_ftype_v2si_puint_char, SPE_BUILTIN_EVSTWWE);
  def_builtin (target_flags, "__builtin_spe_evstwwo", void_ftype_v2si_puint_char, SPE_BUILTIN_EVSTWWO);
  def_builtin (target_flags, "__builtin_spe_evsplatfi", v2si_ftype_signed_char, SPE_BUILTIN_EVSPLATFI);
  def_builtin (target_flags, "__builtin_spe_evsplati", v2si_ftype_signed_char, SPE_BUILTIN_EVSPLATI);

  /* Loads.  */
  def_builtin (target_flags, "__builtin_spe_evlddx", v2si_ftype_pv2si_int, SPE_BUILTIN_EVLDDX);
  def_builtin (target_flags, "__builtin_spe_evldwx", v2si_ftype_pv2si_int, SPE_BUILTIN_EVLDWX);
  def_builtin (target_flags, "__builtin_spe_evldhx", v2si_ftype_pv2si_int, SPE_BUILTIN_EVLDHX);
  def_builtin (target_flags, "__builtin_spe_evlwhex", v2si_ftype_puint_int, SPE_BUILTIN_EVLWHEX);
  def_builtin (target_flags, "__builtin_spe_evlwhoux", v2si_ftype_puint_int, SPE_BUILTIN_EVLWHOUX);
  def_builtin (target_flags, "__builtin_spe_evlwhosx", v2si_ftype_puint_int, SPE_BUILTIN_EVLWHOSX);
  def_builtin (target_flags, "__builtin_spe_evlwwsplatx", v2si_ftype_puint_int, SPE_BUILTIN_EVLWWSPLATX);
  def_builtin (target_flags, "__builtin_spe_evlwhsplatx", v2si_ftype_puint_int, SPE_BUILTIN_EVLWHSPLATX);
  def_builtin (target_flags, "__builtin_spe_evlhhesplatx", v2si_ftype_pushort_int, SPE_BUILTIN_EVLHHESPLATX);
  def_builtin (target_flags, "__builtin_spe_evlhhousplatx", v2si_ftype_pushort_int, SPE_BUILTIN_EVLHHOUSPLATX);
  def_builtin (target_flags, "__builtin_spe_evlhhossplatx", v2si_ftype_pushort_int, SPE_BUILTIN_EVLHHOSSPLATX);
  def_builtin (target_flags, "__builtin_spe_evldd", v2si_ftype_pv2si_int, SPE_BUILTIN_EVLDD);
  def_builtin (target_flags, "__builtin_spe_evldw", v2si_ftype_pv2si_int, SPE_BUILTIN_EVLDW);
  def_builtin (target_flags, "__builtin_spe_evldh", v2si_ftype_pv2si_int, SPE_BUILTIN_EVLDH);
  def_builtin (target_flags, "__builtin_spe_evlhhesplat", v2si_ftype_pushort_int, SPE_BUILTIN_EVLHHESPLAT);
  def_builtin (target_flags, "__builtin_spe_evlhhossplat", v2si_ftype_pushort_int, SPE_BUILTIN_EVLHHOSSPLAT);
  def_builtin (target_flags, "__builtin_spe_evlhhousplat", v2si_ftype_pushort_int, SPE_BUILTIN_EVLHHOUSPLAT);
  def_builtin (target_flags, "__builtin_spe_evlwhe", v2si_ftype_puint_int, SPE_BUILTIN_EVLWHE);
  def_builtin (target_flags, "__builtin_spe_evlwhos", v2si_ftype_puint_int, SPE_BUILTIN_EVLWHOS);
  def_builtin (target_flags, "__builtin_spe_evlwhou", v2si_ftype_puint_int, SPE_BUILTIN_EVLWHOU);
  def_builtin (target_flags, "__builtin_spe_evlwhsplat", v2si_ftype_puint_int, SPE_BUILTIN_EVLWHSPLAT);
  def_builtin (target_flags, "__builtin_spe_evlwwsplat", v2si_ftype_puint_int, SPE_BUILTIN_EVLWWSPLAT);

  /* Predicates.  */
  d = (struct builtin_description *) bdesc_spe_predicates;
  for (i = 0; i < ARRAY_SIZE (bdesc_spe_predicates); ++i, d++)
    {
      tree type;

      switch (insn_data[d->icode].operand[1].mode)
	{
	case V2SImode:
	  type = int_ftype_int_v2si_v2si;
	  break;
	case V2SFmode:
	  type = int_ftype_int_v2sf_v2sf;
	  break;
	default:
	  gcc_unreachable ();
	}

      def_builtin (d->mask, d->name, type, d->code);
    }

  /* Evsel predicates.  */
  d = (struct builtin_description *) bdesc_spe_evsel;
  for (i = 0; i < ARRAY_SIZE (bdesc_spe_evsel); ++i, d++)
    {
      tree type;

      switch (insn_data[d->icode].operand[1].mode)
	{
	case V2SImode:
	  type = v2si_ftype_4_v2si;
	  break;
	case V2SFmode:
	  type = v2sf_ftype_4_v2sf;
	  break;
	default:
	  gcc_unreachable ();
	}

      def_builtin (d->mask, d->name, type, d->code);
    }
}