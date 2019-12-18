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
struct ia64_pal_retval {int /*<<< orphan*/  status; int /*<<< orphan*/  v1; int /*<<< orphan*/  v0; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  PAL_CALL_STK (struct ia64_pal_retval,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAL_VP_ENV_INFO ; 

__attribute__((used)) static inline s64 ia64_pal_vp_env_info(u64 *buffer_size,
		u64 *vp_env_info)
{
	struct ia64_pal_retval iprv;
	PAL_CALL_STK(iprv, PAL_VP_ENV_INFO, 0, 0, 0);
	*buffer_size = iprv.v0;
	*vp_env_info = iprv.v1;
	return iprv.status;
}