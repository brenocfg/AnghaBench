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
struct f_audio_buf {struct f_audio_buf* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct f_audio_buf*) ; 

__attribute__((used)) static void f_audio_buffer_free(struct f_audio_buf *audio_buf)
{
	kfree(audio_buf->buf);
	kfree(audio_buf);
}