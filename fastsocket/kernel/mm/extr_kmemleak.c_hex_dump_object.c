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
typedef  int /*<<< orphan*/  u8 ;
struct seq_file {int dummy; } ;
struct kmemleak_object {int size; scalar_t__ pointer; } ;
typedef  int /*<<< orphan*/  linebuf ;

/* Variables and functions */
 int /*<<< orphan*/  HEX_ASCII ; 
 int /*<<< orphan*/  HEX_GROUP_SIZE ; 
 int HEX_MAX_LINES ; 
 int HEX_ROW_SIZE ; 
 int /*<<< orphan*/  hex_dump_to_buffer (int /*<<< orphan*/  const*,int,int,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static void hex_dump_object(struct seq_file *seq,
			    struct kmemleak_object *object)
{
	const u8 *ptr = (const u8 *)object->pointer;
	int i, len, remaining;
	unsigned char linebuf[HEX_ROW_SIZE * 5];

	/* limit the number of lines to HEX_MAX_LINES */
	remaining = len =
		min(object->size, (size_t)(HEX_MAX_LINES * HEX_ROW_SIZE));

	seq_printf(seq, "  hex dump (first %d bytes):\n", len);
	for (i = 0; i < len; i += HEX_ROW_SIZE) {
		int linelen = min(remaining, HEX_ROW_SIZE);

		remaining -= HEX_ROW_SIZE;
		hex_dump_to_buffer(ptr + i, linelen, HEX_ROW_SIZE,
				   HEX_GROUP_SIZE, linebuf, sizeof(linebuf),
				   HEX_ASCII);
		seq_printf(seq, "    %s\n", linebuf);
	}
}