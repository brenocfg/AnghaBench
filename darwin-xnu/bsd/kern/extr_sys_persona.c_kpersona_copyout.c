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
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  scalar_t__ uint32_t ;
struct kpersona_info {int dummy; } ;
typedef  int /*<<< orphan*/  info_v ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PERSONA_INFO_V1 ; 
 int copyin (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int copyout (struct kpersona_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kpersona_copyout(struct kpersona_info *kinfo, user_addr_t infop)
{
	uint32_t info_v;
	int error;

	error = copyin(infop, &info_v, sizeof(info_v));
	if (error)
		return error;

	/* only support a single version of the struct for now */
	/* TODO: in the future compare info_v to kinfo->persona_info_version */
	if (info_v != PERSONA_INFO_V1)
		return EINVAL;

	error = copyout(kinfo, infop, sizeof(*kinfo));
	return error;
}