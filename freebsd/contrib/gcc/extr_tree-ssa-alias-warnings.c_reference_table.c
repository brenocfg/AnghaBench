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
struct reference_matches {int dummy; } ;

/* Variables and functions */
 struct reference_matches* build_reference_table () ; 
 int /*<<< orphan*/  find_references_in_function () ; 
 struct reference_matches* ref_table ; 

__attribute__((used)) static inline struct reference_matches *
reference_table (bool build)
{
  if (ref_table || !build)
    return ref_table;

  ref_table = build_reference_table ();
  find_references_in_function ();
  return ref_table;
}