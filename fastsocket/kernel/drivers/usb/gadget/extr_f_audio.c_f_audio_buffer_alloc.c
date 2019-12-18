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
struct f_audio_buf {void* buf; } ;

/* Variables and functions */
 scalar_t__ ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (struct f_audio_buf*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct f_audio_buf *f_audio_buffer_alloc(int buf_size)
{
	struct f_audio_buf *copy_buf;

	copy_buf = kzalloc(sizeof *copy_buf, GFP_ATOMIC);
	if (!copy_buf)
		return (struct f_audio_buf *)-ENOMEM;

	copy_buf->buf = kzalloc(buf_size, GFP_ATOMIC);
	if (!copy_buf->buf) {
		kfree(copy_buf);
		return (struct f_audio_buf *)-ENOMEM;
	}

	return copy_buf;
}