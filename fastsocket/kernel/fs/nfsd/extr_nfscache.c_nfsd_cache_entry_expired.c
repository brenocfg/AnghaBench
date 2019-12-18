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
struct svc_cacherep {scalar_t__ c_state; scalar_t__ c_timestamp; } ;

/* Variables and functions */
 scalar_t__ RC_EXPIRE ; 
 scalar_t__ RC_INPROG ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline bool
nfsd_cache_entry_expired(struct svc_cacherep *rp)
{
	return rp->c_state != RC_INPROG &&
	       time_after(jiffies, rp->c_timestamp + RC_EXPIRE);
}