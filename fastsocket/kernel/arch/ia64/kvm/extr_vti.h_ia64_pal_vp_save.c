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
typedef  int /*<<< orphan*/  u64 ;
struct ia64_pal_retval {int /*<<< orphan*/  status; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  PAL_CALL_STK (struct ia64_pal_retval,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAL_VP_SAVE ; 

__attribute__((used)) static inline s64 ia64_pal_vp_save(u64 *vpd, u64 pal_proc_vector)
{
	struct ia64_pal_retval iprv;

	PAL_CALL_STK(iprv, PAL_VP_SAVE, (u64)vpd, pal_proc_vector, 0);

	return iprv.status;
}