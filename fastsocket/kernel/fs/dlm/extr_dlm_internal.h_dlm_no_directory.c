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
struct dlm_ls {int ls_exflags; } ;

/* Variables and functions */
 int DLM_LSFL_NODIR ; 

__attribute__((used)) static inline int dlm_no_directory(struct dlm_ls *ls)
{
	return (ls->ls_exflags & DLM_LSFL_NODIR) ? 1 : 0;
}