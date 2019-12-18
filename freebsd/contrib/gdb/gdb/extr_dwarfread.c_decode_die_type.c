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
struct type {int dummy; } ;
struct dieinfo {scalar_t__ at_fund_type; scalar_t__ at_mod_u_d_type; scalar_t__ at_user_def_type; int /*<<< orphan*/ * at_mod_fund_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  FT_VOID ; 
 struct type* alloc_utype (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_objfile ; 
 struct type* decode_fund_type (scalar_t__) ; 
 struct type* decode_mod_fund_type (int /*<<< orphan*/ *) ; 
 struct type* decode_mod_u_d_type (scalar_t__) ; 
 struct type* dwarf_fundamental_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct type* lookup_utype (scalar_t__) ; 

__attribute__((used)) static struct type *
decode_die_type (struct dieinfo *dip)
{
  struct type *type = NULL;

  if (dip->at_fund_type != 0)
    {
      type = decode_fund_type (dip->at_fund_type);
    }
  else if (dip->at_mod_fund_type != NULL)
    {
      type = decode_mod_fund_type (dip->at_mod_fund_type);
    }
  else if (dip->at_user_def_type)
    {
      type = lookup_utype (dip->at_user_def_type);
      if (type == NULL)
	{
	  type = alloc_utype (dip->at_user_def_type, NULL);
	}
    }
  else if (dip->at_mod_u_d_type)
    {
      type = decode_mod_u_d_type (dip->at_mod_u_d_type);
    }
  else
    {
      type = dwarf_fundamental_type (current_objfile, FT_VOID);
    }
  return (type);
}