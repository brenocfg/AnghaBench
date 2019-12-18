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
struct firedtv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCODE_LOCK_COMPARE_SWAP ; 
 int node_req (struct firedtv*,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int node_lock(struct firedtv *fdtv, u64 addr, void *data)
{
	return node_req(fdtv, addr, data, 8, TCODE_LOCK_COMPARE_SWAP);
}