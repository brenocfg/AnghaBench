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
struct td {int /*<<< orphan*/  frame_lh; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct td*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_td(struct td *td)
{
	memset(td, 0, sizeof(*td));
	INIT_LIST_HEAD(&td->node);
	INIT_LIST_HEAD(&td->frame_lh);
}