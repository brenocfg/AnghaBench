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
struct insn_ent {struct insn_def* def; } ;
struct insn_def {int /*<<< orphan*/  insn_code; int /*<<< orphan*/  vec_idx; int /*<<< orphan*/  def; struct insn_def* next; } ;
struct attr_value {int dummy; } ;
struct attr_desc {struct attr_value* default_val; int /*<<< orphan*/  name; scalar_t__ is_const; } ;
typedef  int /*<<< orphan*/ * rtx ;

/* Variables and functions */
 int /*<<< orphan*/ * XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XSTR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ XVEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct insn_def* defs ; 
 struct attr_value* get_attr_value (int /*<<< orphan*/ *,struct attr_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_insn_ent (struct attr_value*,struct insn_ent*) ; 
 struct insn_ent* oballoc (int) ; 
 int /*<<< orphan*/  strcmp_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fill_attr (struct attr_desc *attr)
{
  struct attr_value *av;
  struct insn_ent *ie;
  struct insn_def *id;
  int i;
  rtx value;

  /* Don't fill constant attributes.  The value is independent of
     any particular insn.  */
  if (attr->is_const)
    return;

  for (id = defs; id; id = id->next)
    {
      /* If no value is specified for this insn for this attribute, use the
	 default.  */
      value = NULL;
      if (XVEC (id->def, id->vec_idx))
	for (i = 0; i < XVECLEN (id->def, id->vec_idx); i++)
	  if (! strcmp_check (XSTR (XEXP (XVECEXP (id->def, id->vec_idx, i), 0), 0),
			      attr->name))
	    value = XEXP (XVECEXP (id->def, id->vec_idx, i), 1);

      if (value == NULL)
	av = attr->default_val;
      else
	av = get_attr_value (value, attr, id->insn_code);

      ie = oballoc (sizeof (struct insn_ent));
      ie->def = id;
      insert_insn_ent (av, ie);
    }
}