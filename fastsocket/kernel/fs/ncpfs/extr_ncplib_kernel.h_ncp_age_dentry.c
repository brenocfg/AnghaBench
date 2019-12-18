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
struct ncp_server {scalar_t__ dentry_ttl; } ;
struct dentry {scalar_t__ d_time; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 

__attribute__((used)) static inline void
ncp_age_dentry(struct ncp_server* server, struct dentry* dentry)
{
	dentry->d_time = jiffies - server->dentry_ttl;
}