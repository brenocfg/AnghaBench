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
struct super_block {struct super_block* s_options; struct super_block* s_subtype; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_sb_writers (struct super_block*) ; 
 int /*<<< orphan*/  kfree (struct super_block*) ; 
 int /*<<< orphan*/  security_sb_free (struct super_block*) ; 

__attribute__((used)) static inline void destroy_super(struct super_block *s)
{
	security_sb_free(s);
	destroy_sb_writers(s);
	kfree(s->s_subtype);
	kfree(s->s_options);
	kfree(s);
}