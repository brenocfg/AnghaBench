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
struct frame {int /*<<< orphan*/  alloced; int /*<<< orphan*/  payload; int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct carlu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 struct frame* carlu_alloc_frame (struct carlu*,int) ; 
 int /*<<< orphan*/  frame_free (struct frame*) ; 
 int /*<<< orphan*/  frame_push (struct frame*,int) ; 
 int /*<<< orphan*/  frame_put (struct frame*,int) ; 
 int /*<<< orphan*/  frame_reserve (struct frame*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  print_hex_dump_bytes (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void carlu_frame_test(struct carlu *ar)
{
	struct frame *frame;

	frame = carlu_alloc_frame(ar, 0x40);
	frame_reserve(frame, 0x10);

	memset(frame_put(frame, 0x10), 0x11, 0x10);
	memset(frame_put(frame, 0x10), 0x22, 0x10);
	memset(frame_push(frame, 0x10), 0x33, 0x10);
	memset(frame_put(frame, 0x10), 0x44, 0x10);

	print_hex_dump_bytes(INFO, "DATA:", frame->data, frame->len);

	print_hex_dump_bytes(INFO, "PAYLOAD:", frame->payload, frame->alloced);

	frame_free(frame);
}