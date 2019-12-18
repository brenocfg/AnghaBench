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
#define  BLKFLSBUF 138 
#define  BLKROSET 137 
#define  NBD_CLEAR_QUE 136 
#define  NBD_CLEAR_SOCK 135 
#define  NBD_DISCONNECT 134 
#define  NBD_DO_IT 133 
#define  NBD_PRINT_DEBUG 132 
#define  NBD_SET_BLKSIZE 131 
#define  NBD_SET_SIZE 130 
#define  NBD_SET_SIZE_BLOCKS 129 
#define  NBD_SET_SOCK 128 

__attribute__((used)) static const char *ioctl_cmd_to_ascii(int cmd)
{
	switch (cmd) {
	case NBD_SET_SOCK: return "set-sock";
	case NBD_SET_BLKSIZE: return "set-blksize";
	case NBD_SET_SIZE: return "set-size";
	case NBD_DO_IT: return "do-it";
	case NBD_CLEAR_SOCK: return "clear-sock";
	case NBD_CLEAR_QUE: return "clear-que";
	case NBD_PRINT_DEBUG: return "print-debug";
	case NBD_SET_SIZE_BLOCKS: return "set-size-blocks";
	case NBD_DISCONNECT: return "disconnect";
	case BLKROSET: return "set-read-only";
	case BLKFLSBUF: return "flush-buffer-cache";
	}
	return "unknown";
}