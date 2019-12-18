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
struct set {void* dest_addr_elt; void* src_elt; void* dest; void* src; } ;
typedef  void* rtx ;

/* Variables and functions */
 scalar_t__ COND_EXEC ; 
 void* COND_EXEC_CODE (void*) ; 
 void* COND_EXEC_TEST (void*) ; 
 scalar_t__ GET_CODE (void*) ; 
 int /*<<< orphan*/  GET_MODE (void*) ; 
 int MAX_SETS ; 
 scalar_t__ MEM_P (void*) ; 
 scalar_t__ PARALLEL ; 
 void* PATTERN (void*) ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ REG_P (void*) ; 
 scalar_t__ SET ; 
 void* SET_DEST (void*) ; 
 void* SET_SRC (void*) ; 
 scalar_t__ STRICT_LOW_PART ; 
 void* XEXP (void*,int /*<<< orphan*/ ) ; 
 void* XVECEXP (void*,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ asm_noperands (void*) ; 
 int /*<<< orphan*/  cselib_invalidate_rtx_note_stores ; 
 void* cselib_lookup (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ cselib_record_memory ; 
 int /*<<< orphan*/  cselib_record_set (void*,void*,void*) ; 
 void* gen_rtx_IF_THEN_ELSE (int /*<<< orphan*/ ,void*,void*,void*) ; 
 int /*<<< orphan*/  note_stores (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* pc_rtx ; 
 scalar_t__ rtx_equal_p (void*,void*) ; 

__attribute__((used)) static void
cselib_record_sets (rtx insn)
{
  int n_sets = 0;
  int i;
  struct set sets[MAX_SETS];
  rtx body = PATTERN (insn);
  rtx cond = 0;

  body = PATTERN (insn);
  if (GET_CODE (body) == COND_EXEC)
    {
      cond = COND_EXEC_TEST (body);
      body = COND_EXEC_CODE (body);
    }

  /* Find all sets.  */
  if (GET_CODE (body) == SET)
    {
      sets[0].src = SET_SRC (body);
      sets[0].dest = SET_DEST (body);
      n_sets = 1;
    }
  else if (GET_CODE (body) == PARALLEL)
    {
      /* Look through the PARALLEL and record the values being
	 set, if possible.  Also handle any CLOBBERs.  */
      for (i = XVECLEN (body, 0) - 1; i >= 0; --i)
	{
	  rtx x = XVECEXP (body, 0, i);

	  if (GET_CODE (x) == SET)
	    {
	      sets[n_sets].src = SET_SRC (x);
	      sets[n_sets].dest = SET_DEST (x);
	      n_sets++;
	    }
	}
    }

  /* Look up the values that are read.  Do this before invalidating the
     locations that are written.  */
  for (i = 0; i < n_sets; i++)
    {
      rtx dest = sets[i].dest;

      /* A STRICT_LOW_PART can be ignored; we'll record the equivalence for
         the low part after invalidating any knowledge about larger modes.  */
      if (GET_CODE (sets[i].dest) == STRICT_LOW_PART)
	sets[i].dest = dest = XEXP (dest, 0);

      /* We don't know how to record anything but REG or MEM.  */
      if (REG_P (dest)
	  || (MEM_P (dest) && cselib_record_memory))
        {
	  rtx src = sets[i].src;
	  if (cond)
	    src = gen_rtx_IF_THEN_ELSE (GET_MODE (src), cond, src, dest);
	  sets[i].src_elt = cselib_lookup (src, GET_MODE (dest), 1);
	  if (MEM_P (dest))
	    sets[i].dest_addr_elt = cselib_lookup (XEXP (dest, 0), Pmode, 1);
	  else
	    sets[i].dest_addr_elt = 0;
	}
    }

  /* Invalidate all locations written by this insn.  Note that the elts we
     looked up in the previous loop aren't affected, just some of their
     locations may go away.  */
  note_stores (body, cselib_invalidate_rtx_note_stores, NULL);

  /* If this is an asm, look for duplicate sets.  This can happen when the
     user uses the same value as an output multiple times.  This is valid
     if the outputs are not actually used thereafter.  Treat this case as
     if the value isn't actually set.  We do this by smashing the destination
     to pc_rtx, so that we won't record the value later.  */
  if (n_sets >= 2 && asm_noperands (body) >= 0)
    {
      for (i = 0; i < n_sets; i++)
	{
	  rtx dest = sets[i].dest;
	  if (REG_P (dest) || MEM_P (dest))
	    {
	      int j;
	      for (j = i + 1; j < n_sets; j++)
		if (rtx_equal_p (dest, sets[j].dest))
		  {
		    sets[i].dest = pc_rtx;
		    sets[j].dest = pc_rtx;
		  }
	    }
	}
    }

  /* Now enter the equivalences in our tables.  */
  for (i = 0; i < n_sets; i++)
    {
      rtx dest = sets[i].dest;
      if (REG_P (dest)
	  || (MEM_P (dest) && cselib_record_memory))
	cselib_record_set (dest, sets[i].src_elt, sets[i].dest_addr_elt);
    }
}