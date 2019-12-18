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
struct ehca_top_bmap {int /*<<< orphan*/ * dir; } ;
struct ehca_dir_bmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHCA_ENT_MAP_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ehca_bmap_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ehca_init_top_bmap(struct ehca_top_bmap *ehca_top_bmap,
				     int dir)
{
	if (!ehca_bmap_valid(ehca_top_bmap->dir[dir])) {
		ehca_top_bmap->dir[dir] =
			kmalloc(sizeof(struct ehca_dir_bmap), GFP_KERNEL);
		if (!ehca_top_bmap->dir[dir])
			return -ENOMEM;
		/* Set map block to 0xFF according to EHCA_INVAL_ADDR */
		memset(ehca_top_bmap->dir[dir], 0xFF, EHCA_ENT_MAP_SIZE);
	}
	return 0;
}