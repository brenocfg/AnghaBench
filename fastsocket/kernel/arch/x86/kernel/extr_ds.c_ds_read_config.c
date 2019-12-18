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
struct ds_trace {void* ith; void* end; void* top; void* begin; } ;
struct ds_context {unsigned char* ds; } ;
typedef  enum ds_qualifier { ____Placeholder_ds_qualifier } ds_qualifier ;

/* Variables and functions */
 int /*<<< orphan*/  ds_absolute_maximum ; 
 int /*<<< orphan*/  ds_buffer_base ; 
 scalar_t__ ds_get (unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds_index ; 
 int /*<<< orphan*/  ds_interrupt_threshold ; 

__attribute__((used)) static void ds_read_config(struct ds_context *context,
			   struct ds_trace *cfg, enum ds_qualifier qual)
{
	unsigned char *ds = context->ds;

	cfg->begin = (void *)ds_get(ds, qual, ds_buffer_base);
	cfg->top = (void *)ds_get(ds, qual, ds_index);
	cfg->end = (void *)ds_get(ds, qual, ds_absolute_maximum);
	cfg->ith = (void *)ds_get(ds, qual, ds_interrupt_threshold);
}