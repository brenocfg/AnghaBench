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
struct ehca_top_bmap {int dummy; } ;
struct ehca_bmap {int /*<<< orphan*/ * top; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHCA_DIR_MAP_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ehca_bmap_valid (int /*<<< orphan*/ ) ; 
 int ehca_init_top_bmap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ehca_init_bmap(struct ehca_bmap *ehca_bmap, int top, int dir)
{
	if (!ehca_bmap_valid(ehca_bmap->top[top])) {
		ehca_bmap->top[top] =
			kmalloc(sizeof(struct ehca_top_bmap), GFP_KERNEL);
		if (!ehca_bmap->top[top])
			return -ENOMEM;
		/* Set map block to 0xFF according to EHCA_INVAL_ADDR */
		memset(ehca_bmap->top[top], 0xFF, EHCA_DIR_MAP_SIZE);
	}
	return ehca_init_top_bmap(ehca_bmap->top[top], dir);
}