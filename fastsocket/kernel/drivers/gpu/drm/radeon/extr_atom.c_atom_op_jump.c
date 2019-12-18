#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int last_jump; int start; unsigned long last_jump_jiffies; int abort; TYPE_1__* ctx; } ;
typedef  TYPE_2__ atom_exec_context ;
struct TYPE_4__ {int cs_above; int cs_equal; } ;

/* Variables and functions */
#define  ATOM_COND_ABOVE 134 
#define  ATOM_COND_ABOVEOREQUAL 133 
#define  ATOM_COND_ALWAYS 132 
#define  ATOM_COND_BELOW 131 
#define  ATOM_COND_BELOWOREQUAL 130 
#define  ATOM_COND_EQUAL 129 
#define  ATOM_COND_NOTEQUAL 128 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  SDEBUG (char*,...) ; 
 int U16 (int) ; 
 void* jiffies ; 
 int jiffies_to_msecs (unsigned long) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static void atom_op_jump(atom_exec_context *ctx, int *ptr, int arg)
{
	int execute = 0, target = U16(*ptr);
	unsigned long cjiffies;

	(*ptr) += 2;
	switch (arg) {
	case ATOM_COND_ABOVE:
		execute = ctx->ctx->cs_above;
		break;
	case ATOM_COND_ABOVEOREQUAL:
		execute = ctx->ctx->cs_above || ctx->ctx->cs_equal;
		break;
	case ATOM_COND_ALWAYS:
		execute = 1;
		break;
	case ATOM_COND_BELOW:
		execute = !(ctx->ctx->cs_above || ctx->ctx->cs_equal);
		break;
	case ATOM_COND_BELOWOREQUAL:
		execute = !ctx->ctx->cs_above;
		break;
	case ATOM_COND_EQUAL:
		execute = ctx->ctx->cs_equal;
		break;
	case ATOM_COND_NOTEQUAL:
		execute = !ctx->ctx->cs_equal;
		break;
	}
	if (arg != ATOM_COND_ALWAYS)
		SDEBUG("   taken: %s\n", execute ? "yes" : "no");
	SDEBUG("   target: 0x%04X\n", target);
	if (execute) {
		if (ctx->last_jump == (ctx->start + target)) {
			cjiffies = jiffies;
			if (time_after(cjiffies, ctx->last_jump_jiffies)) {
				cjiffies -= ctx->last_jump_jiffies;
				if ((jiffies_to_msecs(cjiffies) > 5000)) {
					DRM_ERROR("atombios stuck in loop for more than 5secs aborting\n");
					ctx->abort = true;
				}
			} else {
				/* jiffies wrap around we will just wait a little longer */
				ctx->last_jump_jiffies = jiffies;
			}
		} else {
			ctx->last_jump = ctx->start + target;
			ctx->last_jump_jiffies = jiffies;
		}
		*ptr = ctx->start + target;
	}
}