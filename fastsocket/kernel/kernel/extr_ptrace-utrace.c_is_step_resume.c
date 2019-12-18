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
typedef  enum utrace_resume_action { ____Placeholder_utrace_resume_action } utrace_resume_action ;

/* Variables and functions */
 int UTRACE_BLOCKSTEP ; 
 int UTRACE_SINGLESTEP ; 

__attribute__((used)) static inline bool is_step_resume(enum utrace_resume_action resume)
{
	return resume == UTRACE_BLOCKSTEP || resume == UTRACE_SINGLESTEP;
}