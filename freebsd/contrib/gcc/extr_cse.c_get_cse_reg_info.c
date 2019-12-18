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
struct cse_reg_info {scalar_t__ timestamp; } ;

/* Variables and functions */
 struct cse_reg_info* cse_reg_info_table ; 
 scalar_t__ cse_reg_info_timestamp ; 
 int /*<<< orphan*/  get_cse_reg_info_1 (unsigned int) ; 

__attribute__((used)) static inline struct cse_reg_info *
get_cse_reg_info (unsigned int regno)
{
  struct cse_reg_info *p = &cse_reg_info_table[regno];

  /* If this entry has not been initialized, go ahead and initialize
     it.  */
  if (p->timestamp != cse_reg_info_timestamp)
    get_cse_reg_info_1 (regno);

  return p;
}