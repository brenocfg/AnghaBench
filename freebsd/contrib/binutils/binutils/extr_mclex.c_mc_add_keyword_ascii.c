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
typedef  int /*<<< orphan*/  unichar ;
typedef  int /*<<< orphan*/  rc_uint_type ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  mc_add_keyword (int /*<<< orphan*/ *,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unicode_from_codepage (int /*<<< orphan*/ *,int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mc_add_keyword_ascii (const char *sz, int rid, const char *grp, rc_uint_type nv, const char *sv)
{
  unichar *usz, *usv = NULL;
  rc_uint_type usz_len;

  unicode_from_codepage (&usz_len, &usz, sz, CP_ACP);
  if (sv)
    unicode_from_codepage (&usz_len, &usv, sv, CP_ACP);
  mc_add_keyword (usz, rid, grp, nv, usv);
}