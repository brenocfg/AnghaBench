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
struct MidiBuffer {int pos_read; int pos_write; int size; } ;

/* Variables and functions */
 scalar_t__ midibuf_is_full (struct MidiBuffer*) ; 

int midibuf_bytes_free(struct MidiBuffer *this)
{
	return
		midibuf_is_full(this) ?
		0 :
		(this->pos_read - this->pos_write + this->size - 1) % this->size + 1;
}