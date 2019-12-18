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
typedef  int /*<<< orphan*/  smd_channel_t ;

/* Variables and functions */
 int EINVAL ; 
 int ch_read (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  notify_other_smd () ; 

__attribute__((used)) static int smd_stream_read(smd_channel_t *ch, void *data, int len)
{
	int r;

	if (len < 0)
		return -EINVAL;

	r = ch_read(ch, data, len);
	if (r > 0)
		notify_other_smd();

	return r;
}