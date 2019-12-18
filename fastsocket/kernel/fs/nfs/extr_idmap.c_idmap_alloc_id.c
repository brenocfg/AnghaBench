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
struct idmap_hashtable {int dummy; } ;
struct idmap_hashent {int dummy; } ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  idmap_alloc_hashtable (struct idmap_hashtable*) ; 
 struct idmap_hashent* idmap_id_hash (struct idmap_hashtable*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct idmap_hashent *
idmap_alloc_id(struct idmap_hashtable *h, __u32 id)
{
	idmap_alloc_hashtable(h);
	return idmap_id_hash(h, id);
}