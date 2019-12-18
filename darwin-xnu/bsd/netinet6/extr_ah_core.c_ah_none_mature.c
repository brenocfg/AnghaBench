#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct secasvar {TYPE_2__* sah; } ;
struct TYPE_3__ {scalar_t__ proto; } ;
struct TYPE_4__ {TYPE_1__ saidx; } ;

/* Variables and functions */
 scalar_t__ IPPROTO_AH ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  ipseclog (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ah_none_mature(struct secasvar *sav)
{
	if (sav->sah->saidx.proto == IPPROTO_AH) {
		ipseclog((LOG_ERR,
		    "ah_none_mature: protocol and algorithm mismatch.\n"));
		return 1;
	}
	return 0;
}