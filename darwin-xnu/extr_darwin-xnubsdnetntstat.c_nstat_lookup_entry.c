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
typedef  int /*<<< orphan*/  u_int32_t ;
typedef  int /*<<< orphan*/  nstat_provider_id_t ;
typedef  int /*<<< orphan*/  nstat_provider_cookie_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* nstat_lookup ) (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ nstat_provider ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 TYPE_1__* nstat_find_provider_by_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static errno_t
nstat_lookup_entry(
	nstat_provider_id_t		id,
	const void				*data,
	u_int32_t				length,
	nstat_provider			**out_provider,
	nstat_provider_cookie_t	*out_cookie)
{
	*out_provider = nstat_find_provider_by_id(id);
	if (*out_provider == NULL)
	{
		return ENOENT;
	}

	return (*out_provider)->nstat_lookup(data, length, out_cookie);
}