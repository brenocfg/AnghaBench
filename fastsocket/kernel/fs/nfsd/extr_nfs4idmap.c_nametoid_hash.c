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
struct ent {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENT_HASHBITS ; 
 int hash_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
nametoid_hash(struct ent *ent)
{
	return hash_str(ent->name, ENT_HASHBITS);
}