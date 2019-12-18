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
struct TYPE_8__ {TYPE_3__* bsp; TYPE_3__* stack; } ;
struct TYPE_6__ {TYPE_1__* types; } ;
struct ieee_info {TYPE_4__ blockstack; TYPE_2__ types; void* dhandle; } ;
typedef  scalar_t__ debug_type ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_7__ {unsigned int fnindx; } ;
struct TYPE_5__ {scalar_t__* arg_slots; } ;

/* Variables and functions */
 scalar_t__ DEBUG_KIND_POINTER ; 
 scalar_t__ DEBUG_TYPE_NULL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ debug_get_target_type (void*,scalar_t__) ; 
 scalar_t__ debug_get_type_kind (void*,scalar_t__) ; 
 scalar_t__ debug_make_reference_type (void*,scalar_t__) ; 
 int /*<<< orphan*/  ieee_error (struct ieee_info*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee_require_asn (struct ieee_info*,int /*<<< orphan*/  const**,int*) ; 
 int /*<<< orphan*/  ieee_require_atn65 (struct ieee_info*,int /*<<< orphan*/  const**,char const**,unsigned long*) ; 

__attribute__((used)) static bfd_boolean
ieee_read_cxx_defaults (struct ieee_info *info, const bfd_byte **pp,
			unsigned long count)
{
  const bfd_byte *start;
  const char *fnname;
  unsigned long fnlen;
  bfd_vma defcount;

  start = *pp;

  /* Giving the function name before the argument count is an addendum
     to the spec.  The function name is demangled, though, so this
     record must always refer to the current function.  */

  if (info->blockstack.bsp <= info->blockstack.stack
      || info->blockstack.bsp[-1].fnindx == (unsigned int) -1)
    {
      ieee_error (info, start, _("C++ default values not in a function"));
      return FALSE;
    }

  if (! ieee_require_atn65 (info, pp, &fnname, &fnlen)
      || ! ieee_require_asn (info, pp, &defcount))
    return FALSE;
  count -= 2;

  while (defcount-- > 0)
    {
      bfd_vma type, val;
      const char *strval;
      unsigned long strvallen;

      if (! ieee_require_asn (info, pp, &type))
	return FALSE;
      --count;

      switch (type)
	{
	case 0:
	case 4:
	  break;

	case 1:
	case 2:
	  if (! ieee_require_asn (info, pp, &val))
	    return FALSE;
	  --count;
	  break;

	case 3:
	case 7:
	  if (! ieee_require_atn65 (info, pp, &strval, &strvallen))
	    return FALSE;
	  --count;
	  break;

	default:
	  ieee_error (info, start, _("unrecognized C++ default type"));
	  return FALSE;
	}

      /* We have no way to record the default argument values, so we
         just ignore them.  FIXME.  */
    }

  /* Any remaining arguments are indices of parameters that are really
     reference type.  */
  if (count > 0)
    {
      void *dhandle;
      debug_type *arg_slots;

      dhandle = info->dhandle;
      arg_slots = info->types.types[info->blockstack.bsp[-1].fnindx].arg_slots;
      while (count-- > 0)
	{
	  bfd_vma indx;
	  debug_type target;

	  if (! ieee_require_asn (info, pp, &indx))
	    return FALSE;
	  /* The index is 1 based.  */
	  --indx;
	  if (arg_slots == NULL
	      || arg_slots[indx] == DEBUG_TYPE_NULL
	      || (debug_get_type_kind (dhandle, arg_slots[indx])
		  != DEBUG_KIND_POINTER))
	    {
	      ieee_error (info, start, _("reference parameter is not a pointer"));
	      return FALSE;
	    }

	  target = debug_get_target_type (dhandle, arg_slots[indx]);
	  arg_slots[indx] = debug_make_reference_type (dhandle, target);
	  if (arg_slots[indx] == DEBUG_TYPE_NULL)
	    return FALSE;
	}
    }

  return TRUE;
}