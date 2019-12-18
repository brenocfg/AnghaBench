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

/* Variables and functions */
 unsigned int debugifc_count_nonwhitespace (char const*,unsigned int) ; 
 unsigned int debugifc_count_whitespace (char const*,unsigned int) ; 

__attribute__((used)) static unsigned int debugifc_isolate_word(const char *buf,unsigned int count,
					  const char **wstrPtr,
					  unsigned int *wlenPtr)
{
	const char *wptr;
	unsigned int consume_cnt = 0;
	unsigned int wlen;
	unsigned int scnt;

	wptr = NULL;
	wlen = 0;
	scnt = debugifc_count_whitespace(buf,count);
	consume_cnt += scnt; count -= scnt; buf += scnt;
	if (!count) goto done;

	scnt = debugifc_count_nonwhitespace(buf,count);
	if (!scnt) goto done;
	wptr = buf;
	wlen = scnt;
	consume_cnt += scnt; count -= scnt; buf += scnt;

 done:
	*wstrPtr = wptr;
	*wlenPtr = wlen;
	return consume_cnt;
}