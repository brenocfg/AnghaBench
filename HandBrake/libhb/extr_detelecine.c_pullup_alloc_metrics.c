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
struct pullup_field {void* var; void* comb; void* diffs; } ;
struct pullup_context {int /*<<< orphan*/  metric_len; } ;

/* Variables and functions */
 void* calloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pullup_alloc_metrics( struct pullup_context * c,
                                  struct pullup_field * f )
{
    f->diffs = calloc( c->metric_len, sizeof(int) );
    f->comb  = calloc( c->metric_len, sizeof(int) );
    f->var   = calloc( c->metric_len, sizeof(int) );
}