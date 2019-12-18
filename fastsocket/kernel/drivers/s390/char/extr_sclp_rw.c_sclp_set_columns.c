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
struct sclp_buffer {unsigned short columns; scalar_t__ current_length; int /*<<< orphan*/ * current_line; } ;

/* Variables and functions */
 int /*<<< orphan*/  sclp_finalize_mto (struct sclp_buffer*) ; 

void
sclp_set_columns(struct sclp_buffer *buffer, unsigned short columns)
{
	buffer->columns = columns;
	if (buffer->current_line != NULL &&
	    buffer->current_length > buffer->columns)
		sclp_finalize_mto(buffer);
}