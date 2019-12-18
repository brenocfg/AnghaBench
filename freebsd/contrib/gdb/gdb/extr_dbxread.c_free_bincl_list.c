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
struct objfile {int /*<<< orphan*/  md; } ;

/* Variables and functions */
 int /*<<< orphan*/  bincl_list ; 
 scalar_t__ bincls_allocated ; 
 int /*<<< orphan*/  xmfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_bincl_list (struct objfile *objfile)
{
  xmfree (objfile->md, bincl_list);
  bincls_allocated = 0;
}