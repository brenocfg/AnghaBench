#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct builtin_description {scalar_t__ name; size_t icode; int /*<<< orphan*/  code; int /*<<< orphan*/  mask; } ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_4__ {TYPE_1__* operand; } ;
struct TYPE_3__ {int mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALTIVEC_BUILTIN_OVERLOADED_FIRST ; 
 int /*<<< orphan*/  ALTIVEC_BUILTIN_OVERLOADED_LAST ; 
 size_t ARRAY_SIZE (scalar_t__) ; 
 size_t CODE_FOR_nothing ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int QImode ; 
#define  SImode 135 
 int /*<<< orphan*/  V16QI_type_node ; 
#define  V16QImode 134 
#define  V2SFmode 133 
#define  V2SImode 132 
 int /*<<< orphan*/  V4SF_type_node ; 
#define  V4SFmode 131 
 int /*<<< orphan*/  V4SI_type_node ; 
#define  V4SImode 130 
 int /*<<< orphan*/  V8HI_type_node ; 
#define  V8HImode 129 
#define  VOIDmode 128 
 scalar_t__ bdesc_1arg ; 
 scalar_t__ bdesc_2arg ; 
 scalar_t__ bdesc_3arg ; 
 int /*<<< orphan*/  build_function_type_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  char_type_node ; 
 int /*<<< orphan*/  def_builtin (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 TYPE_2__* insn_data ; 
 int /*<<< orphan*/  integer_type_node ; 
 int /*<<< orphan*/  opaque_V2SF_type_node ; 
 int /*<<< orphan*/  opaque_V2SI_type_node ; 
 int /*<<< orphan*/  opaque_V4SI_type_node ; 

__attribute__((used)) static void
rs6000_common_init_builtins (void)
{
  struct builtin_description *d;
  size_t i;

  tree v4sf_ftype_v4sf_v4sf_v16qi
    = build_function_type_list (V4SF_type_node,
				V4SF_type_node, V4SF_type_node,
				V16QI_type_node, NULL_TREE);
  tree v4si_ftype_v4si_v4si_v16qi
    = build_function_type_list (V4SI_type_node,
				V4SI_type_node, V4SI_type_node,
				V16QI_type_node, NULL_TREE);
  tree v8hi_ftype_v8hi_v8hi_v16qi
    = build_function_type_list (V8HI_type_node,
				V8HI_type_node, V8HI_type_node,
				V16QI_type_node, NULL_TREE);
  tree v16qi_ftype_v16qi_v16qi_v16qi
    = build_function_type_list (V16QI_type_node,
				V16QI_type_node, V16QI_type_node,
				V16QI_type_node, NULL_TREE);
  tree v4si_ftype_int
    = build_function_type_list (V4SI_type_node, integer_type_node, NULL_TREE);
  tree v8hi_ftype_int
    = build_function_type_list (V8HI_type_node, integer_type_node, NULL_TREE);
  tree v16qi_ftype_int
    = build_function_type_list (V16QI_type_node, integer_type_node, NULL_TREE);
  tree v8hi_ftype_v16qi
    = build_function_type_list (V8HI_type_node, V16QI_type_node, NULL_TREE);
  tree v4sf_ftype_v4sf
    = build_function_type_list (V4SF_type_node, V4SF_type_node, NULL_TREE);

  tree v2si_ftype_v2si_v2si
    = build_function_type_list (opaque_V2SI_type_node,
				opaque_V2SI_type_node,
				opaque_V2SI_type_node, NULL_TREE);

  tree v2sf_ftype_v2sf_v2sf
    = build_function_type_list (opaque_V2SF_type_node,
				opaque_V2SF_type_node,
				opaque_V2SF_type_node, NULL_TREE);

  tree v2si_ftype_int_int
    = build_function_type_list (opaque_V2SI_type_node,
				integer_type_node, integer_type_node,
				NULL_TREE);

  tree opaque_ftype_opaque
    = build_function_type_list (opaque_V4SI_type_node,
				opaque_V4SI_type_node, NULL_TREE);

  tree v2si_ftype_v2si
    = build_function_type_list (opaque_V2SI_type_node,
				opaque_V2SI_type_node, NULL_TREE);

  tree v2sf_ftype_v2sf
    = build_function_type_list (opaque_V2SF_type_node,
				opaque_V2SF_type_node, NULL_TREE);

  tree v2sf_ftype_v2si
    = build_function_type_list (opaque_V2SF_type_node,
				opaque_V2SI_type_node, NULL_TREE);

  tree v2si_ftype_v2sf
    = build_function_type_list (opaque_V2SI_type_node,
				opaque_V2SF_type_node, NULL_TREE);

  tree v2si_ftype_v2si_char
    = build_function_type_list (opaque_V2SI_type_node,
				opaque_V2SI_type_node,
				char_type_node, NULL_TREE);

  tree v2si_ftype_int_char
    = build_function_type_list (opaque_V2SI_type_node,
				integer_type_node, char_type_node, NULL_TREE);

  tree v2si_ftype_char
    = build_function_type_list (opaque_V2SI_type_node,
				char_type_node, NULL_TREE);

  tree int_ftype_int_int
    = build_function_type_list (integer_type_node,
				integer_type_node, integer_type_node,
				NULL_TREE);

  tree opaque_ftype_opaque_opaque
    = build_function_type_list (opaque_V4SI_type_node,
                                opaque_V4SI_type_node, opaque_V4SI_type_node, NULL_TREE);
  tree v4si_ftype_v4si_v4si
    = build_function_type_list (V4SI_type_node,
				V4SI_type_node, V4SI_type_node, NULL_TREE);
  tree v4sf_ftype_v4si_int
    = build_function_type_list (V4SF_type_node,
				V4SI_type_node, integer_type_node, NULL_TREE);
  tree v4si_ftype_v4sf_int
    = build_function_type_list (V4SI_type_node,
				V4SF_type_node, integer_type_node, NULL_TREE);
  tree v4si_ftype_v4si_int
    = build_function_type_list (V4SI_type_node,
				V4SI_type_node, integer_type_node, NULL_TREE);
  tree v8hi_ftype_v8hi_int
    = build_function_type_list (V8HI_type_node,
				V8HI_type_node, integer_type_node, NULL_TREE);
  tree v16qi_ftype_v16qi_int
    = build_function_type_list (V16QI_type_node,
				V16QI_type_node, integer_type_node, NULL_TREE);
  tree v16qi_ftype_v16qi_v16qi_int
    = build_function_type_list (V16QI_type_node,
				V16QI_type_node, V16QI_type_node,
				integer_type_node, NULL_TREE);
  tree v8hi_ftype_v8hi_v8hi_int
    = build_function_type_list (V8HI_type_node,
				V8HI_type_node, V8HI_type_node,
				integer_type_node, NULL_TREE);
  tree v4si_ftype_v4si_v4si_int
    = build_function_type_list (V4SI_type_node,
				V4SI_type_node, V4SI_type_node,
				integer_type_node, NULL_TREE);
  tree v4sf_ftype_v4sf_v4sf_int
    = build_function_type_list (V4SF_type_node,
				V4SF_type_node, V4SF_type_node,
				integer_type_node, NULL_TREE);
  tree v4sf_ftype_v4sf_v4sf
    = build_function_type_list (V4SF_type_node,
				V4SF_type_node, V4SF_type_node, NULL_TREE);
  tree opaque_ftype_opaque_opaque_opaque
    = build_function_type_list (opaque_V4SI_type_node,
                                opaque_V4SI_type_node, opaque_V4SI_type_node,
                                opaque_V4SI_type_node, NULL_TREE);
  tree v4sf_ftype_v4sf_v4sf_v4si
    = build_function_type_list (V4SF_type_node,
				V4SF_type_node, V4SF_type_node,
				V4SI_type_node, NULL_TREE);
  tree v4sf_ftype_v4sf_v4sf_v4sf
    = build_function_type_list (V4SF_type_node,
				V4SF_type_node, V4SF_type_node,
				V4SF_type_node, NULL_TREE);
  tree v4si_ftype_v4si_v4si_v4si
    = build_function_type_list (V4SI_type_node,
				V4SI_type_node, V4SI_type_node,
				V4SI_type_node, NULL_TREE);
  tree v8hi_ftype_v8hi_v8hi
    = build_function_type_list (V8HI_type_node,
				V8HI_type_node, V8HI_type_node, NULL_TREE);
  tree v8hi_ftype_v8hi_v8hi_v8hi
    = build_function_type_list (V8HI_type_node,
				V8HI_type_node, V8HI_type_node,
				V8HI_type_node, NULL_TREE);
  tree v4si_ftype_v8hi_v8hi_v4si
    = build_function_type_list (V4SI_type_node,
				V8HI_type_node, V8HI_type_node,
				V4SI_type_node, NULL_TREE);
  tree v4si_ftype_v16qi_v16qi_v4si
    = build_function_type_list (V4SI_type_node,
				V16QI_type_node, V16QI_type_node,
				V4SI_type_node, NULL_TREE);
  tree v16qi_ftype_v16qi_v16qi
    = build_function_type_list (V16QI_type_node,
				V16QI_type_node, V16QI_type_node, NULL_TREE);
  tree v4si_ftype_v4sf_v4sf
    = build_function_type_list (V4SI_type_node,
				V4SF_type_node, V4SF_type_node, NULL_TREE);
  tree v8hi_ftype_v16qi_v16qi
    = build_function_type_list (V8HI_type_node,
				V16QI_type_node, V16QI_type_node, NULL_TREE);
  tree v4si_ftype_v8hi_v8hi
    = build_function_type_list (V4SI_type_node,
				V8HI_type_node, V8HI_type_node, NULL_TREE);
  tree v8hi_ftype_v4si_v4si
    = build_function_type_list (V8HI_type_node,
				V4SI_type_node, V4SI_type_node, NULL_TREE);
  tree v16qi_ftype_v8hi_v8hi
    = build_function_type_list (V16QI_type_node,
				V8HI_type_node, V8HI_type_node, NULL_TREE);
  tree v4si_ftype_v16qi_v4si
    = build_function_type_list (V4SI_type_node,
				V16QI_type_node, V4SI_type_node, NULL_TREE);
  tree v4si_ftype_v16qi_v16qi
    = build_function_type_list (V4SI_type_node,
				V16QI_type_node, V16QI_type_node, NULL_TREE);
  tree v4si_ftype_v8hi_v4si
    = build_function_type_list (V4SI_type_node,
				V8HI_type_node, V4SI_type_node, NULL_TREE);
  tree v4si_ftype_v8hi
    = build_function_type_list (V4SI_type_node, V8HI_type_node, NULL_TREE);
  tree int_ftype_v4si_v4si
    = build_function_type_list (integer_type_node,
				V4SI_type_node, V4SI_type_node, NULL_TREE);
  tree int_ftype_v4sf_v4sf
    = build_function_type_list (integer_type_node,
				V4SF_type_node, V4SF_type_node, NULL_TREE);
  tree int_ftype_v16qi_v16qi
    = build_function_type_list (integer_type_node,
				V16QI_type_node, V16QI_type_node, NULL_TREE);
  tree int_ftype_v8hi_v8hi
    = build_function_type_list (integer_type_node,
				V8HI_type_node, V8HI_type_node, NULL_TREE);

  /* Add the simple ternary operators.  */
  d = (struct builtin_description *) bdesc_3arg;
  for (i = 0; i < ARRAY_SIZE (bdesc_3arg); i++, d++)
    {
      enum machine_mode mode0, mode1, mode2, mode3;
      tree type;
      bool is_overloaded = d->code >= ALTIVEC_BUILTIN_OVERLOADED_FIRST
			   && d->code <= ALTIVEC_BUILTIN_OVERLOADED_LAST;

      if (is_overloaded)
	{
          mode0 = VOIDmode;
          mode1 = VOIDmode;
          mode2 = VOIDmode;
          mode3 = VOIDmode;
	}
      else
	{
          if (d->name == 0 || d->icode == CODE_FOR_nothing)
	    continue;

          mode0 = insn_data[d->icode].operand[0].mode;
          mode1 = insn_data[d->icode].operand[1].mode;
          mode2 = insn_data[d->icode].operand[2].mode;
          mode3 = insn_data[d->icode].operand[3].mode;
	}

      /* When all four are of the same mode.  */
      if (mode0 == mode1 && mode1 == mode2 && mode2 == mode3)
	{
	  switch (mode0)
	    {
	    case VOIDmode:
	      type = opaque_ftype_opaque_opaque_opaque;
	      break;
	    case V4SImode:
	      type = v4si_ftype_v4si_v4si_v4si;
	      break;
	    case V4SFmode:
	      type = v4sf_ftype_v4sf_v4sf_v4sf;
	      break;
	    case V8HImode:
	      type = v8hi_ftype_v8hi_v8hi_v8hi;
	      break;
	    case V16QImode:
	      type = v16qi_ftype_v16qi_v16qi_v16qi;
	      break;
	    default:
	      gcc_unreachable ();
	    }
	}
      else if (mode0 == mode1 && mode1 == mode2 && mode3 == V16QImode)
	{
	  switch (mode0)
	    {
	    case V4SImode:
	      type = v4si_ftype_v4si_v4si_v16qi;
	      break;
	    case V4SFmode:
	      type = v4sf_ftype_v4sf_v4sf_v16qi;
	      break;
	    case V8HImode:
	      type = v8hi_ftype_v8hi_v8hi_v16qi;
	      break;
	    case V16QImode:
	      type = v16qi_ftype_v16qi_v16qi_v16qi;
	      break;
	    default:
	      gcc_unreachable ();
	    }
	}
      else if (mode0 == V4SImode && mode1 == V16QImode && mode2 == V16QImode
	       && mode3 == V4SImode)
	type = v4si_ftype_v16qi_v16qi_v4si;
      else if (mode0 == V4SImode && mode1 == V8HImode && mode2 == V8HImode
	       && mode3 == V4SImode)
	type = v4si_ftype_v8hi_v8hi_v4si;
      else if (mode0 == V4SFmode && mode1 == V4SFmode && mode2 == V4SFmode
	       && mode3 == V4SImode)
	type = v4sf_ftype_v4sf_v4sf_v4si;

      /* vchar, vchar, vchar, 4 bit literal.  */
      else if (mode0 == V16QImode && mode1 == mode0 && mode2 == mode0
	       && mode3 == QImode)
	type = v16qi_ftype_v16qi_v16qi_int;

      /* vshort, vshort, vshort, 4 bit literal.  */
      else if (mode0 == V8HImode && mode1 == mode0 && mode2 == mode0
	       && mode3 == QImode)
	type = v8hi_ftype_v8hi_v8hi_int;

      /* vint, vint, vint, 4 bit literal.  */
      else if (mode0 == V4SImode && mode1 == mode0 && mode2 == mode0
	       && mode3 == QImode)
	type = v4si_ftype_v4si_v4si_int;

      /* vfloat, vfloat, vfloat, 4 bit literal.  */
      else if (mode0 == V4SFmode && mode1 == mode0 && mode2 == mode0
	       && mode3 == QImode)
	type = v4sf_ftype_v4sf_v4sf_int;

      else
	gcc_unreachable ();

      def_builtin (d->mask, d->name, type, d->code);
    }

  /* Add the simple binary operators.  */
  d = (struct builtin_description *) bdesc_2arg;
  for (i = 0; i < ARRAY_SIZE (bdesc_2arg); i++, d++)
    {
      enum machine_mode mode0, mode1, mode2;
      tree type;
      bool is_overloaded = d->code >= ALTIVEC_BUILTIN_OVERLOADED_FIRST
			   && d->code <= ALTIVEC_BUILTIN_OVERLOADED_LAST;

      if (is_overloaded)
	{
	  mode0 = VOIDmode;
	  mode1 = VOIDmode;
	  mode2 = VOIDmode;
	}
      else
	{
          if (d->name == 0 || d->icode == CODE_FOR_nothing)
	    continue;

          mode0 = insn_data[d->icode].operand[0].mode;
          mode1 = insn_data[d->icode].operand[1].mode;
          mode2 = insn_data[d->icode].operand[2].mode;
	}

      /* When all three operands are of the same mode.  */
      if (mode0 == mode1 && mode1 == mode2)
	{
	  switch (mode0)
	    {
	    case VOIDmode:
	      type = opaque_ftype_opaque_opaque;
	      break;
	    case V4SFmode:
	      type = v4sf_ftype_v4sf_v4sf;
	      break;
	    case V4SImode:
	      type = v4si_ftype_v4si_v4si;
	      break;
	    case V16QImode:
	      type = v16qi_ftype_v16qi_v16qi;
	      break;
	    case V8HImode:
	      type = v8hi_ftype_v8hi_v8hi;
	      break;
	    case V2SImode:
	      type = v2si_ftype_v2si_v2si;
	      break;
	    case V2SFmode:
	      type = v2sf_ftype_v2sf_v2sf;
	      break;
	    case SImode:
	      type = int_ftype_int_int;
	      break;
	    default:
	      gcc_unreachable ();
	    }
	}

      /* A few other combos we really don't want to do manually.  */

      /* vint, vfloat, vfloat.  */
      else if (mode0 == V4SImode && mode1 == V4SFmode && mode2 == V4SFmode)
	type = v4si_ftype_v4sf_v4sf;

      /* vshort, vchar, vchar.  */
      else if (mode0 == V8HImode && mode1 == V16QImode && mode2 == V16QImode)
	type = v8hi_ftype_v16qi_v16qi;

      /* vint, vshort, vshort.  */
      else if (mode0 == V4SImode && mode1 == V8HImode && mode2 == V8HImode)
	type = v4si_ftype_v8hi_v8hi;

      /* vshort, vint, vint.  */
      else if (mode0 == V8HImode && mode1 == V4SImode && mode2 == V4SImode)
	type = v8hi_ftype_v4si_v4si;

      /* vchar, vshort, vshort.  */
      else if (mode0 == V16QImode && mode1 == V8HImode && mode2 == V8HImode)
	type = v16qi_ftype_v8hi_v8hi;

      /* vint, vchar, vint.  */
      else if (mode0 == V4SImode && mode1 == V16QImode && mode2 == V4SImode)
	type = v4si_ftype_v16qi_v4si;

      /* vint, vchar, vchar.  */
      else if (mode0 == V4SImode && mode1 == V16QImode && mode2 == V16QImode)
	type = v4si_ftype_v16qi_v16qi;

      /* vint, vshort, vint.  */
      else if (mode0 == V4SImode && mode1 == V8HImode && mode2 == V4SImode)
	type = v4si_ftype_v8hi_v4si;

      /* vint, vint, 5 bit literal.  */
      else if (mode0 == V4SImode && mode1 == V4SImode && mode2 == QImode)
	type = v4si_ftype_v4si_int;

      /* vshort, vshort, 5 bit literal.  */
      else if (mode0 == V8HImode && mode1 == V8HImode && mode2 == QImode)
	type = v8hi_ftype_v8hi_int;

      /* vchar, vchar, 5 bit literal.  */
      else if (mode0 == V16QImode && mode1 == V16QImode && mode2 == QImode)
	type = v16qi_ftype_v16qi_int;

      /* vfloat, vint, 5 bit literal.  */
      else if (mode0 == V4SFmode && mode1 == V4SImode && mode2 == QImode)
	type = v4sf_ftype_v4si_int;

      /* vint, vfloat, 5 bit literal.  */
      else if (mode0 == V4SImode && mode1 == V4SFmode && mode2 == QImode)
	type = v4si_ftype_v4sf_int;

      else if (mode0 == V2SImode && mode1 == SImode && mode2 == SImode)
	type = v2si_ftype_int_int;

      else if (mode0 == V2SImode && mode1 == V2SImode && mode2 == QImode)
	type = v2si_ftype_v2si_char;

      else if (mode0 == V2SImode && mode1 == SImode && mode2 == QImode)
	type = v2si_ftype_int_char;

      else
	{
	  /* int, x, x.  */
	  gcc_assert (mode0 == SImode);
	  switch (mode1)
	    {
	    case V4SImode:
	      type = int_ftype_v4si_v4si;
	      break;
	    case V4SFmode:
	      type = int_ftype_v4sf_v4sf;
	      break;
	    case V16QImode:
	      type = int_ftype_v16qi_v16qi;
	      break;
	    case V8HImode:
	      type = int_ftype_v8hi_v8hi;
	      break;
	    default:
	      gcc_unreachable ();
	    }
	}

      def_builtin (d->mask, d->name, type, d->code);
    }

  /* Add the simple unary operators.  */
  d = (struct builtin_description *) bdesc_1arg;
  for (i = 0; i < ARRAY_SIZE (bdesc_1arg); i++, d++)
    {
      enum machine_mode mode0, mode1;
      tree type;
      bool is_overloaded = d->code >= ALTIVEC_BUILTIN_OVERLOADED_FIRST
			   && d->code <= ALTIVEC_BUILTIN_OVERLOADED_LAST;

      if (is_overloaded)
        {
          mode0 = VOIDmode;
          mode1 = VOIDmode;
        }
      else
        {
          if (d->name == 0 || d->icode == CODE_FOR_nothing)
	    continue;

          mode0 = insn_data[d->icode].operand[0].mode;
          mode1 = insn_data[d->icode].operand[1].mode;
        }

      if (mode0 == V4SImode && mode1 == QImode)
	type = v4si_ftype_int;
      else if (mode0 == V8HImode && mode1 == QImode)
	type = v8hi_ftype_int;
      else if (mode0 == V16QImode && mode1 == QImode)
	type = v16qi_ftype_int;
      else if (mode0 == VOIDmode && mode1 == VOIDmode)
	type = opaque_ftype_opaque;
      else if (mode0 == V4SFmode && mode1 == V4SFmode)
	type = v4sf_ftype_v4sf;
      else if (mode0 == V8HImode && mode1 == V16QImode)
	type = v8hi_ftype_v16qi;
      else if (mode0 == V4SImode && mode1 == V8HImode)
	type = v4si_ftype_v8hi;
      else if (mode0 == V2SImode && mode1 == V2SImode)
	type = v2si_ftype_v2si;
      else if (mode0 == V2SFmode && mode1 == V2SFmode)
	type = v2sf_ftype_v2sf;
      else if (mode0 == V2SFmode && mode1 == V2SImode)
	type = v2sf_ftype_v2si;
      else if (mode0 == V2SImode && mode1 == V2SFmode)
	type = v2si_ftype_v2sf;
      else if (mode0 == V2SImode && mode1 == QImode)
	type = v2si_ftype_char;
      else
	gcc_unreachable ();

      def_builtin (d->mask, d->name, type, d->code);
    }
}