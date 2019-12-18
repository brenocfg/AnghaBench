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
struct il_priv {int /*<<< orphan*/  free_frames; } ;
struct il_frame {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct il_frame*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
il4965_free_frame(struct il_priv *il, struct il_frame *frame)
{
	memset(frame, 0, sizeof(*frame));
	list_add(&frame->list, &il->free_frames);
}