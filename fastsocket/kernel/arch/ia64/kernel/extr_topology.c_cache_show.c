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
struct kobject {int dummy; } ;
struct cache_info {int dummy; } ;
struct cache_attr {int /*<<< orphan*/  (* show ) (struct cache_info*,char*) ;} ;
struct attribute {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct cache_info*,char*) ; 
 struct cache_attr* to_attr (struct attribute*) ; 
 struct cache_info* to_object (struct kobject*) ; 

__attribute__((used)) static ssize_t cache_show(struct kobject * kobj, struct attribute * attr, char * buf)
{
	struct cache_attr *fattr = to_attr(attr);
	struct cache_info *this_leaf = to_object(kobj);
	ssize_t ret;

	ret = fattr->show ? fattr->show(this_leaf, buf) : 0;
	return ret;
}