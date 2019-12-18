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
struct cred {int dummy; } ;
struct cachefiles_cache {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  revert_creds (struct cred const*) ; 

__attribute__((used)) static inline void cachefiles_end_secure(struct cachefiles_cache *cache,
					 const struct cred *saved_cred)
{
	revert_creds(saved_cred);
}