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
struct dsthash_ent {int /*<<< orphan*/  dst; } ;
struct dsthash_dst {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,struct dsthash_dst const*,int) ; 

__attribute__((used)) static inline bool dst_cmp(const struct dsthash_ent *ent,
			   const struct dsthash_dst *b)
{
	return !memcmp(&ent->dst, b, sizeof(ent->dst));
}