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
struct rewriteConfigState {int /*<<< orphan*/  rewritten; int /*<<< orphan*/  option_to_line; int /*<<< orphan*/  numlines; int /*<<< orphan*/  lines; } ;

/* Variables and functions */
 int /*<<< orphan*/  dictRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfreesplitres (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (struct rewriteConfigState*) ; 

void rewriteConfigReleaseState(struct rewriteConfigState *state) {
    sdsfreesplitres(state->lines,state->numlines);
    dictRelease(state->option_to_line);
    dictRelease(state->rewritten);
    zfree(state);
}