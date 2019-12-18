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
typedef  int uint32_t ;
struct dlm_ls {int ls_dirtbl_size; } ;

/* Variables and functions */
 int jhash (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t dir_hash(struct dlm_ls *ls, char *name, int len)
{
	uint32_t val;

	val = jhash(name, len, 0);
	val &= (ls->ls_dirtbl_size - 1);

	return val;
}