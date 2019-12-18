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
struct trace_seq {int len; int readpos; scalar_t__ buffer; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EBUSY ; 
 size_t EFAULT ; 
 void* memcpy (void*,scalar_t__,size_t) ; 

__attribute__((used)) static ssize_t trace_seq_to_buffer(struct trace_seq *s, void *buf, size_t cnt)
{
	int len;
	void *ret;

	if (s->len <= s->readpos)
		return -EBUSY;

	len = s->len - s->readpos;
	if (cnt > len)
		cnt = len;
	ret = memcpy(buf, s->buffer + s->readpos, cnt);
	if (!ret)
		return -EFAULT;

	s->readpos += cnt;
	return cnt;
}