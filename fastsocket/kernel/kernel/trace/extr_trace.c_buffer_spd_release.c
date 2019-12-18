#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct splice_pipe_desc {TYPE_1__* partial; } ;
struct buffer_ref {int /*<<< orphan*/  page; int /*<<< orphan*/  buffer; scalar_t__ ref; } ;
struct TYPE_2__ {scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct buffer_ref*) ; 
 int /*<<< orphan*/  ring_buffer_free_read_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void buffer_spd_release(struct splice_pipe_desc *spd, unsigned int i)
{
	struct buffer_ref *ref =
		(struct buffer_ref *)spd->partial[i].private;

	if (--ref->ref)
		return;

	ring_buffer_free_read_page(ref->buffer, ref->page);
	kfree(ref);
	spd->partial[i].private = 0;
}