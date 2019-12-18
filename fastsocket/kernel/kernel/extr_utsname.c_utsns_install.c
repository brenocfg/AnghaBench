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
struct nsproxy {void* uts_ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_uts_ns (void*) ; 
 int /*<<< orphan*/  put_uts_ns (void*) ; 

__attribute__((used)) static int utsns_install(struct nsproxy *nsproxy, void *ns)
{
	get_uts_ns(ns);
	put_uts_ns(nsproxy->uts_ns);
	nsproxy->uts_ns = ns;
	return 0;
}