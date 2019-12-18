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
typedef  scalar_t__ tree ;
typedef  enum x86_64_reg_class { ____Placeholder_x86_64_reg_class } x86_64_reg_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_3__ {scalar_t__ (* must_pass_in_stack ) (int,scalar_t__) ;} ;
struct TYPE_4__ {TYPE_1__ calls; } ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ AGGREGATE_TYPE_P (scalar_t__) ; 
#define  ARRAY_TYPE 164 
 int /*<<< orphan*/  BINFO_BASE_ITERATE (scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  BINFO_N_BASE_BINFOS (scalar_t__) ; 
 int /*<<< orphan*/  BINFO_OFFSET (scalar_t__) ; 
 scalar_t__ BINFO_TYPE (scalar_t__) ; 
#define  BLKmode 163 
#define  CDImode 162 
#define  CHImode 161 
 scalar_t__ COMPLEX_MODE_P (int) ; 
#define  CQImode 160 
#define  CSImode 159 
#define  CTImode 158 
#define  DCmode 157 
#define  DDmode 156 
 int /*<<< orphan*/  DECL_BIT_FIELD (scalar_t__) ; 
 int /*<<< orphan*/  DECL_SIZE (scalar_t__) ; 
#define  DFmode 155 
#define  DImode 154 
 int FIELD_DECL ; 
 int GET_MODE_BITSIZE (int) ; 
 int /*<<< orphan*/  GET_MODE_CLASS (int) ; 
 int GET_MODE_INNER (int) ; 
 int GET_MODE_SIZE (int) ; 
#define  HImode 153 
 int MAX_CLASSES ; 
 int /*<<< orphan*/  MODE_INT ; 
#define  QImode 152 
#define  QUAL_UNION_TYPE 151 
#define  RECORD_TYPE 150 
#define  SCmode 149 
#define  SDmode 148 
#define  SFmode 147 
#define  SImode 146 
#define  TCmode 145 
#define  TDmode 144 
#define  TFmode 143 
#define  TImode 142 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_BINFO (scalar_t__) ; 
 scalar_t__ TYPE_FIELDS (scalar_t__) ; 
 int TYPE_MODE (scalar_t__) ; 
#define  UNION_TYPE 141 
 int UNITS_PER_WORD ; 
#define  V16QImode 140 
#define  V2DFmode 139 
#define  V2DImode 138 
#define  V2SFmode 137 
#define  V2SImode 136 
#define  V4HImode 135 
#define  V4SFmode 134 
#define  V4SImode 133 
#define  V8HImode 132 
#define  V8QImode 131 
 int VECTOR_MODE_P (int) ; 
#define  VOIDmode 130 
 int X86_64_COMPLEX_X87_CLASS ; 
 int X86_64_INTEGERSI_CLASS ; 
 int X86_64_INTEGER_CLASS ; 
 int X86_64_MEMORY_CLASS ; 
 int X86_64_NO_CLASS ; 
 int X86_64_SSEDF_CLASS ; 
 int X86_64_SSESF_CLASS ; 
 int X86_64_SSEUP_CLASS ; 
 int X86_64_SSE_CLASS ; 
 int X86_64_X87UP_CLASS ; 
 int X86_64_X87_CLASS ; 
#define  XCmode 129 
#define  XFmode 128 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  int_bit_position (scalar_t__) ; 
 int int_size_in_bytes (scalar_t__) ; 
 int merge_classes (int,int) ; 
 scalar_t__ stub1 (int,scalar_t__) ; 
 TYPE_2__ targetm ; 
 int tree_low_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
classify_argument (enum machine_mode mode, tree type,
		   enum x86_64_reg_class classes[MAX_CLASSES], int bit_offset)
{
  HOST_WIDE_INT bytes =
    (mode == BLKmode) ? int_size_in_bytes (type) : (int) GET_MODE_SIZE (mode);
  int words = (bytes + (bit_offset % 64) / 8 + UNITS_PER_WORD - 1) / UNITS_PER_WORD;

  /* Variable sized entities are always passed/returned in memory.  */
  if (bytes < 0)
    return 0;

  if (mode != VOIDmode
      && targetm.calls.must_pass_in_stack (mode, type))
    return 0;

  if (type && AGGREGATE_TYPE_P (type))
    {
      int i;
      tree field;
      enum x86_64_reg_class subclasses[MAX_CLASSES];

      /* On x86-64 we pass structures larger than 16 bytes on the stack.  */
      if (bytes > 16)
	return 0;

      for (i = 0; i < words; i++)
	classes[i] = X86_64_NO_CLASS;

      /* Zero sized arrays or structures are NO_CLASS.  We return 0 to
	 signalize memory class, so handle it as special case.  */
      if (!words)
	{
	  classes[0] = X86_64_NO_CLASS;
	  return 1;
	}

      /* Classify each field of record and merge classes.  */
      switch (TREE_CODE (type))
	{
	case RECORD_TYPE:
	  /* For classes first merge in the field of the subclasses.  */
	  if (TYPE_BINFO (type))
	    {
	      tree binfo, base_binfo;
	      int basenum;

	      for (binfo = TYPE_BINFO (type), basenum = 0;
		   BINFO_BASE_ITERATE (binfo, basenum, base_binfo); basenum++)
		{
		   int num;
		   int offset = tree_low_cst (BINFO_OFFSET (base_binfo), 0) * 8;
		   tree type = BINFO_TYPE (base_binfo);

		   num = classify_argument (TYPE_MODE (type),
					    type, subclasses,
					    (offset + bit_offset) % 256);
		   if (!num)
		     return 0;
		   for (i = 0; i < num; i++)
		     {
		       int pos = (offset + (bit_offset % 64)) / 8 / 8;
		       classes[i + pos] =
			 merge_classes (subclasses[i], classes[i + pos]);
		     }
		}
	    }
	  /* And now merge the fields of structure.  */
	  for (field = TYPE_FIELDS (type); field; field = TREE_CHAIN (field))
	    {
	      if (TREE_CODE (field) == FIELD_DECL)
		{
		  int num;

		  if (TREE_TYPE (field) == error_mark_node)
		    continue;

		  /* Bitfields are always classified as integer.  Handle them
		     early, since later code would consider them to be
		     misaligned integers.  */
		  if (DECL_BIT_FIELD (field))
		    {
		      for (i = (int_bit_position (field) + (bit_offset % 64)) / 8 / 8;
			   i < ((int_bit_position (field) + (bit_offset % 64))
			        + tree_low_cst (DECL_SIZE (field), 0)
				+ 63) / 8 / 8; i++)
			classes[i] =
			  merge_classes (X86_64_INTEGER_CLASS,
					 classes[i]);
		    }
		  else
		    {
		      num = classify_argument (TYPE_MODE (TREE_TYPE (field)),
					       TREE_TYPE (field), subclasses,
					       (int_bit_position (field)
						+ bit_offset) % 256);
		      if (!num)
			return 0;
		      for (i = 0; i < num; i++)
			{
			  int pos =
			    (int_bit_position (field) + (bit_offset % 64)) / 8 / 8;
			  classes[i + pos] =
			    merge_classes (subclasses[i], classes[i + pos]);
			}
		    }
		}
	    }
	  break;

	case ARRAY_TYPE:
	  /* Arrays are handled as small records.  */
	  {
	    int num;
	    num = classify_argument (TYPE_MODE (TREE_TYPE (type)),
				     TREE_TYPE (type), subclasses, bit_offset);
	    if (!num)
	      return 0;

	    /* The partial classes are now full classes.  */
	    if (subclasses[0] == X86_64_SSESF_CLASS && bytes != 4)
	      subclasses[0] = X86_64_SSE_CLASS;
	    if (subclasses[0] == X86_64_INTEGERSI_CLASS && bytes != 4)
	      subclasses[0] = X86_64_INTEGER_CLASS;

	    for (i = 0; i < words; i++)
	      classes[i] = subclasses[i % num];

	    break;
	  }
	case UNION_TYPE:
	case QUAL_UNION_TYPE:
	  /* Unions are similar to RECORD_TYPE but offset is always 0.
	     */

	  /* Unions are not derived.  */
	  gcc_assert (!TYPE_BINFO (type)
		      || !BINFO_N_BASE_BINFOS (TYPE_BINFO (type)));
	  for (field = TYPE_FIELDS (type); field; field = TREE_CHAIN (field))
	    {
	      if (TREE_CODE (field) == FIELD_DECL)
		{
		  int num;

		  if (TREE_TYPE (field) == error_mark_node)
		    continue;

		  num = classify_argument (TYPE_MODE (TREE_TYPE (field)),
					   TREE_TYPE (field), subclasses,
					   bit_offset);
		  if (!num)
		    return 0;
		  for (i = 0; i < num; i++)
		    classes[i] = merge_classes (subclasses[i], classes[i]);
		}
	    }
	  break;

	default:
	  gcc_unreachable ();
	}

      /* Final merger cleanup.  */
      for (i = 0; i < words; i++)
	{
	  /* If one class is MEMORY, everything should be passed in
	     memory.  */
	  if (classes[i] == X86_64_MEMORY_CLASS)
	    return 0;

	  /* The X86_64_SSEUP_CLASS should be always preceded by
	     X86_64_SSE_CLASS.  */
	  if (classes[i] == X86_64_SSEUP_CLASS
	      && (i == 0 || classes[i - 1] != X86_64_SSE_CLASS))
	    classes[i] = X86_64_SSE_CLASS;

	  /*  X86_64_X87UP_CLASS should be preceded by X86_64_X87_CLASS.  */
	  if (classes[i] == X86_64_X87UP_CLASS
	      && (i == 0 || classes[i - 1] != X86_64_X87_CLASS))
	    classes[i] = X86_64_SSE_CLASS;
	}
      return words;
    }

  /* Compute alignment needed.  We align all types to natural boundaries with
     exception of XFmode that is aligned to 64bits.  */
  if (mode != VOIDmode && mode != BLKmode)
    {
      int mode_alignment = GET_MODE_BITSIZE (mode);

      if (mode == XFmode)
	mode_alignment = 128;
      else if (mode == XCmode)
	mode_alignment = 256;
      if (COMPLEX_MODE_P (mode))
	mode_alignment /= 2;
      /* Misaligned fields are always returned in memory.  */
      if (bit_offset % mode_alignment)
	return 0;
    }

  /* for V1xx modes, just use the base mode */
  if (VECTOR_MODE_P (mode)
      && GET_MODE_SIZE (GET_MODE_INNER (mode)) == bytes)
    mode = GET_MODE_INNER (mode);

  /* Classification of atomic types.  */
  switch (mode)
    {
    case SDmode:
    case DDmode:
      classes[0] = X86_64_SSE_CLASS;
      return 1;
    case TDmode:
      classes[0] = X86_64_SSE_CLASS;
      classes[1] = X86_64_SSEUP_CLASS;
      return 2;
    case DImode:
    case SImode:
    case HImode:
    case QImode:
    case CSImode:
    case CHImode:
    case CQImode:
      if (bit_offset + GET_MODE_BITSIZE (mode) <= 32)
	classes[0] = X86_64_INTEGERSI_CLASS;
      else
	classes[0] = X86_64_INTEGER_CLASS;
      return 1;
    case CDImode:
    case TImode:
      classes[0] = classes[1] = X86_64_INTEGER_CLASS;
      return 2;
    case CTImode:
      return 0;
    case SFmode:
      if (!(bit_offset % 64))
	classes[0] = X86_64_SSESF_CLASS;
      else
	classes[0] = X86_64_SSE_CLASS;
      return 1;
    case DFmode:
      classes[0] = X86_64_SSEDF_CLASS;
      return 1;
    case XFmode:
      classes[0] = X86_64_X87_CLASS;
      classes[1] = X86_64_X87UP_CLASS;
      return 2;
    case TFmode:
      classes[0] = X86_64_SSE_CLASS;
      classes[1] = X86_64_SSEUP_CLASS;
      return 2;
    case SCmode:
      classes[0] = X86_64_SSE_CLASS;
      return 1;
    case DCmode:
      classes[0] = X86_64_SSEDF_CLASS;
      classes[1] = X86_64_SSEDF_CLASS;
      return 2;
    case XCmode:
      classes[0] = X86_64_COMPLEX_X87_CLASS;
      return 1;
    case TCmode:
      /* This modes is larger than 16 bytes.  */
      return 0;
    case V4SFmode:
    case V4SImode:
    case V16QImode:
    case V8HImode:
    case V2DFmode:
    case V2DImode:
      classes[0] = X86_64_SSE_CLASS;
      classes[1] = X86_64_SSEUP_CLASS;
      return 2;
    case V2SFmode:
    case V2SImode:
    case V4HImode:
    case V8QImode:
      classes[0] = X86_64_SSE_CLASS;
      return 1;
    case BLKmode:
    case VOIDmode:
      return 0;
    default:
      gcc_assert (VECTOR_MODE_P (mode));

      if (bytes > 16)
	return 0;

      gcc_assert (GET_MODE_CLASS (GET_MODE_INNER (mode)) == MODE_INT);

      if (bit_offset + GET_MODE_BITSIZE (mode) <= 32)
	classes[0] = X86_64_INTEGERSI_CLASS;
      else
	classes[0] = X86_64_INTEGER_CLASS;
      classes[1] = X86_64_INTEGER_CLASS;
      return 1 + (bytes > 8);
    }
}