#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  palette; int /*<<< orphan*/  tree; } ;
typedef  TYPE_1__ ColorProfile ;

/* Variables and functions */
 int /*<<< orphan*/  color_tree_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lodepng_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void color_profile_cleanup(ColorProfile* profile)
{
  color_tree_cleanup(&profile->tree);
  lodepng_free(profile->palette);
}