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
struct logger_log {size_t size; int /*<<< orphan*/  buffer; } ;
struct logger_entry {int dummy; } ;
typedef  char __u32 ;
typedef  char __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static __u32 get_entry_len(struct logger_log *log, size_t off)
{
	__u16 val;

	switch (log->size - off) {
	case 1:
		memcpy(&val, log->buffer + off, 1);
		memcpy(((char *) &val) + 1, log->buffer, 1);
		break;
	default:
		memcpy(&val, log->buffer + off, 2);
	}

	return sizeof(struct logger_entry) + val;
}