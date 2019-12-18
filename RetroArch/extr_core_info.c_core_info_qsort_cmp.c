#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  display_name; } ;
typedef  TYPE_1__ core_info_t ;

/* Variables and functions */
 scalar_t__ core_info_does_support_any_file (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int core_info_does_support_file (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_info_tmp_list ; 
 int /*<<< orphan*/  core_info_tmp_path ; 
 int strcasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int core_info_qsort_cmp(const void *a_, const void *b_)
{
   const core_info_t *a = (const core_info_t*)a_;
   const core_info_t *b = (const core_info_t*)b_;
   int support_a        = core_info_does_support_file(a, core_info_tmp_path);
   int support_b        = core_info_does_support_file(b, core_info_tmp_path);
#ifdef HAVE_COMPRESSION
   support_a            = support_a ||
      core_info_does_support_any_file(a, core_info_tmp_list);
   support_b            = support_b ||
      core_info_does_support_any_file(b, core_info_tmp_list);
#endif

   if (support_a != support_b)
      return support_b - support_a;
   return strcasecmp(a->display_name, b->display_name);
}