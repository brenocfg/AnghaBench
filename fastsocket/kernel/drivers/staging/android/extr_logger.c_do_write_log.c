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
struct logger_log {scalar_t__ w_off; scalar_t__ buffer; scalar_t__ size; } ;

/* Variables and functions */
 scalar_t__ logger_offset (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,size_t) ; 
 size_t min (size_t,scalar_t__) ; 

__attribute__((used)) static void do_write_log(struct logger_log *log, const void *buf, size_t count)
{
	size_t len;

	len = min(count, log->size - log->w_off);
	memcpy(log->buffer + log->w_off, buf, len);

	if (count != len)
		memcpy(log->buffer, buf + len, count - len);

	log->w_off = logger_offset(log->w_off + count);

}