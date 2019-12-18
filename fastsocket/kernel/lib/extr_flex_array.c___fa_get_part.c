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
struct flex_array_part {int dummy; } ;
struct flex_array {struct flex_array_part** parts; } ;
typedef  int gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLEX_ARRAY_FREE ; 
 int __GFP_ZERO ; 
 struct flex_array_part* kmalloc (int,int) ; 
 int /*<<< orphan*/  memset (struct flex_array_part*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct flex_array_part *
__fa_get_part(struct flex_array *fa, int part_nr, gfp_t flags)
{
	struct flex_array_part *part = fa->parts[part_nr];
	if (!part) {
		part = kmalloc(sizeof(struct flex_array_part), flags);
		if (!part)
			return NULL;
		if (!(flags & __GFP_ZERO))
			memset(part, FLEX_ARRAY_FREE,
				sizeof(struct flex_array_part));
		fa->parts[part_nr] = part;
	}
	return part;
}