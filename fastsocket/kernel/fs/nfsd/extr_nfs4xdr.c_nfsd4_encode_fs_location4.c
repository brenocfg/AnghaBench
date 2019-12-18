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
struct nfsd4_fs_location {int /*<<< orphan*/  path; int /*<<< orphan*/  hosts; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ nfsd4_encode_components (char,int /*<<< orphan*/ ,scalar_t__**,int*) ; 
 scalar_t__ nfsd4_encode_components_esc (char,int /*<<< orphan*/ ,scalar_t__**,int*,char,char) ; 

__attribute__((used)) static __be32 nfsd4_encode_fs_location4(struct nfsd4_fs_location *location,
				    __be32 **pp, int *buflen)
{
	__be32 status;
	__be32 *p = *pp;

	status = nfsd4_encode_components_esc(':', location->hosts, &p, buflen,
						'[', ']');
	if (status)
		return status;
	status = nfsd4_encode_components('/', location->path, &p, buflen);
	if (status)
		return status;
	*pp = p;
	return 0;
}