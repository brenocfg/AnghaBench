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
struct et_occ {int depth; struct et_occ* next; struct et_occ* prev; struct et_occ* parent; int /*<<< orphan*/  min; int /*<<< orphan*/  min_occ; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_path_after (struct et_occ*) ; 
 int /*<<< orphan*/  et_check_sanity (struct et_occ*) ; 
 int /*<<< orphan*/  et_check_tree_sanity (struct et_occ*) ; 
 int /*<<< orphan*/  et_recomp_min (struct et_occ*) ; 
 int /*<<< orphan*/  record_path_before (struct et_occ*) ; 
 int /*<<< orphan*/  set_depth (struct et_occ*,int) ; 
 int /*<<< orphan*/  set_depth_add (struct et_occ*,int) ; 
 int /*<<< orphan*/  set_next (struct et_occ*,struct et_occ*) ; 
 int /*<<< orphan*/  set_prev (struct et_occ*,struct et_occ*) ; 

__attribute__((used)) static void
et_splay (struct et_occ *occ)
{
  struct et_occ *f, *gf, *ggf;
  int occ_depth, f_depth, gf_depth;

#ifdef DEBUG_ET
  record_path_before (occ);
  et_check_tree_sanity (occ);
#endif
 
  while (occ->parent)
    {
      occ_depth = occ->depth;

      f = occ->parent;
      f_depth = f->depth;

      gf = f->parent;

      if (!gf)
	{
	  set_depth_add (occ, f_depth);
	  occ->min_occ = f->min_occ;
	  occ->min = f->min;

	  if (f->prev == occ)
	    {
	      /* zig */
	      set_prev (f, occ->next);
	      set_next (occ, f);
	      set_depth_add (f->prev, occ_depth);
	    }
	  else
	    {
	      /* zag */
	      set_next (f, occ->prev);
	      set_prev (occ, f);
	      set_depth_add (f->next, occ_depth);
	    }
	  set_depth (f, -occ_depth);
	  occ->parent = NULL;

	  et_recomp_min (f);
#ifdef DEBUG_ET
	  et_check_tree_sanity (occ);
	  check_path_after (occ);
#endif
	  return;
	}

      gf_depth = gf->depth;

      set_depth_add (occ, f_depth + gf_depth);
      occ->min_occ = gf->min_occ;
      occ->min = gf->min;

      ggf = gf->parent;

      if (gf->prev == f)
	{
	  if (f->prev == occ)
	    {
	      /* zig zig */
	      set_prev (gf, f->next);
	      set_prev (f, occ->next);
	      set_next (occ, f);
	      set_next (f, gf);

	      set_depth (f, -occ_depth);
	      set_depth_add (f->prev, occ_depth);
	      set_depth (gf, -f_depth);
	      set_depth_add (gf->prev, f_depth);
	    }
	  else
	    {
	      /* zag zig */
	      set_prev (gf, occ->next);
	      set_next (f, occ->prev);
	      set_prev (occ, f);
	      set_next (occ, gf);

	      set_depth (f, -occ_depth);
	      set_depth_add (f->next, occ_depth);
	      set_depth (gf, -occ_depth - f_depth);
	      set_depth_add (gf->prev, occ_depth + f_depth);
	    }
	}
      else
	{
	  if (f->prev == occ)
	    {
	      /* zig zag */
	      set_next (gf, occ->prev);
	      set_prev (f, occ->next);
	      set_prev (occ, gf);
	      set_next (occ, f);

	      set_depth (f, -occ_depth);
	      set_depth_add (f->prev, occ_depth);
	      set_depth (gf, -occ_depth - f_depth);
	      set_depth_add (gf->next, occ_depth + f_depth);
	    }
	  else
	    {
	      /* zag zag */
	      set_next (gf, f->prev);
	      set_next (f, occ->prev);
	      set_prev (occ, f);
	      set_prev (f, gf);

	      set_depth (f, -occ_depth);
	      set_depth_add (f->next, occ_depth);
	      set_depth (gf, -f_depth);
	      set_depth_add (gf->next, f_depth);
	    }
	}

      occ->parent = ggf;
      if (ggf)
	{
	  if (ggf->prev == gf)
	    ggf->prev = occ;
	  else
	    ggf->next = occ;
	}

      et_recomp_min (gf);
      et_recomp_min (f);
#ifdef DEBUG_ET
      et_check_tree_sanity (occ);
#endif
    }

#ifdef DEBUG_ET
  et_check_sanity (occ);
  check_path_after (occ);
#endif
}