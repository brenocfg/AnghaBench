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
struct stripe {scalar_t__ lock; int /*<<< orphan*/  sc; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_4__ {TYPE_1__* locking; } ;
struct TYPE_3__ {scalar_t__ (* lock ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DM_RAID45_EX ; 
 int /*<<< orphan*/  DM_RAID45_SHARED ; 
 int EPERM ; 
 int READ ; 
 TYPE_2__* RS (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
stripe_lock(struct stripe *stripe, int rw, sector_t key)
{
	stripe->lock = RS(stripe->sc)->locking->lock(key, rw == READ ? DM_RAID45_SHARED : DM_RAID45_EX);
	return stripe->lock ? 0 : -EPERM;
}