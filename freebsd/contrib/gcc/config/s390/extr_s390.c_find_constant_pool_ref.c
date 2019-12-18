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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ CONSTANT_POOL_ADDRESS_P (scalar_t__) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 char* GET_RTX_FORMAT (scalar_t__) ; 
 int GET_RTX_LENGTH (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 scalar_t__ SYMBOL_REF ; 
 scalar_t__ UNSPEC ; 
 scalar_t__ UNSPECV_POOL_ENTRY ; 
 scalar_t__ UNSPEC_LTREF ; 
 scalar_t__ UNSPEC_LTREL_BASE ; 
 scalar_t__ UNSPEC_VOLATILE ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XINT (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static void
find_constant_pool_ref (rtx x, rtx *ref)
{
  int i, j;
  const char *fmt;

  /* Ignore LTREL_BASE references.  */
  if (GET_CODE (x) == UNSPEC
      && XINT (x, 1) == UNSPEC_LTREL_BASE)
    return;
  /* Likewise POOL_ENTRY insns.  */
  if (GET_CODE (x) == UNSPEC_VOLATILE
      && XINT (x, 1) == UNSPECV_POOL_ENTRY)
    return;

  gcc_assert (GET_CODE (x) != SYMBOL_REF
              || !CONSTANT_POOL_ADDRESS_P (x));

  if (GET_CODE (x) == UNSPEC && XINT (x, 1) == UNSPEC_LTREF)
    {
      rtx sym = XVECEXP (x, 0, 0);
      gcc_assert (GET_CODE (sym) == SYMBOL_REF
	          && CONSTANT_POOL_ADDRESS_P (sym));

      if (*ref == NULL_RTX)
	*ref = sym;
      else 
	gcc_assert (*ref == sym);

      return;
    }

  fmt = GET_RTX_FORMAT (GET_CODE (x));
  for (i = GET_RTX_LENGTH (GET_CODE (x)) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
        {
          find_constant_pool_ref (XEXP (x, i), ref);
        }
      else if (fmt[i] == 'E')
        {
          for (j = 0; j < XVECLEN (x, i); j++)
            find_constant_pool_ref (XVECEXP (x, i, j), ref);
        }
    }
}