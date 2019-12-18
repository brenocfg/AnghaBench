#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nfsd4_compoundres {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  si_opaque; int /*<<< orphan*/  si_generation; } ;
typedef  TYPE_1__ stateid_t ;
typedef  int /*<<< orphan*/  stateid_opaque_t ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  ADJUST_ARGS () ; 
 int /*<<< orphan*/  RESERVE_SPACE (int) ; 
 int /*<<< orphan*/  WRITE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITEMEM (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
nfsd4_encode_stateid(struct nfsd4_compoundres *resp, stateid_t *sid)
{
	__be32 *p;

	RESERVE_SPACE(sizeof(stateid_t));
	WRITE32(sid->si_generation);
	WRITEMEM(&sid->si_opaque, sizeof(stateid_opaque_t));
	ADJUST_ARGS();
}