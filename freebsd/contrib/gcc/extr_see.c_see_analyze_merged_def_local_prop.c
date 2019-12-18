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
struct see_register_properties {int bitmap_index; scalar_t__ first_se_after_last_def; struct see_occr* avail_occr; int /*<<< orphan*/  regno; } ;
struct see_ref_s {void* insn; } ;
struct see_pre_extension_expr {int bitmap_index; scalar_t__ first_se_after_last_def; struct see_occr* avail_occr; int /*<<< orphan*/  regno; } ;
struct see_occr {int block_num; struct see_occr* next; void* insn; } ;
typedef  void* rtx ;
typedef  struct see_register_properties* htab_t ;

/* Variables and functions */
 int BLOCK_NUM (void*) ; 
 int /*<<< orphan*/  DEF_EXTENSION ; 
 scalar_t__ DF_INSN_LUID (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  INSERT ; 
 int /*<<< orphan*/  REGNO (void*) ; 
 int /*<<< orphan*/  RESET_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SET_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ae_kill ; 
 int /*<<< orphan*/ * comp ; 
 int /*<<< orphan*/  df ; 
 int /*<<< orphan*/  gcc_assert (struct see_register_properties*) ; 
 scalar_t__ htab_find_slot (struct see_register_properties*,struct see_register_properties*,int /*<<< orphan*/ ) ; 
 struct see_register_properties** see_bb_hash_ar ; 
 void* see_get_extension_reg (void*,int) ; 
 struct see_register_properties* see_seek_pre_extension_expr (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * transp ; 
 struct see_occr* xmalloc (int) ; 

__attribute__((used)) static int
see_analyze_merged_def_local_prop (void **slot, void *b)
{
  rtx def_se = *slot;
  struct see_ref_s *curr_ref_s = (struct see_ref_s *) b;
  rtx ref = curr_ref_s->insn;
  struct see_pre_extension_expr *extension_expr;
  int indx;
  int bb_num = BLOCK_NUM (ref);
  htab_t curr_bb_hash;
  struct see_register_properties *curr_prop, **slot_prop;
  struct see_register_properties temp_prop;
  rtx dest_extension_reg = see_get_extension_reg (def_se, 1);
  struct see_occr *curr_occr = NULL;
  struct see_occr *tmp_occr = NULL;

  extension_expr = see_seek_pre_extension_expr (def_se, DEF_EXTENSION);
  /* The extension_expr must be found.  */
  gcc_assert (extension_expr);

  curr_bb_hash = see_bb_hash_ar[bb_num];
  gcc_assert (curr_bb_hash);
  temp_prop.regno = REGNO (dest_extension_reg);
  slot_prop =
    (struct see_register_properties **) htab_find_slot (curr_bb_hash,
							&temp_prop, INSERT);
  curr_prop = *slot_prop;
  gcc_assert (curr_prop);

  indx = extension_expr->bitmap_index;

  /* Reset the transparency bit.  */
  RESET_BIT (transp[bb_num], indx);
  /* Reset the killed bit.  */
  RESET_BIT (ae_kill[bb_num], indx);

  if (curr_prop->first_se_after_last_def == DF_INSN_LUID (df, ref))
    {
      /* Set the available bit.  */
      SET_BIT (comp[bb_num], indx);
      /* Record the available occurrence.  */
      curr_occr = xmalloc (sizeof (struct see_occr));
      curr_occr->next = NULL;
      curr_occr->insn = def_se;
      curr_occr->block_num = bb_num;
      tmp_occr = extension_expr->avail_occr;
      if (!tmp_occr)
	extension_expr->avail_occr = curr_occr;
      else
	{
	  while (tmp_occr->next)
	    tmp_occr = tmp_occr->next;
	  tmp_occr->next = curr_occr;
	}
    }

  return 1;
}