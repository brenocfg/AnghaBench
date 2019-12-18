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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_empty_dir_priv {int seen_dot; int seen_dot_dot; int seen_other; scalar_t__ dx_dir; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ OCFS2_DIR_REC_LEN (int) ; 
 int /*<<< orphan*/  strncmp (char*,char const*,int) ; 

__attribute__((used)) static int ocfs2_empty_dir_filldir(void *priv, const char *name, int name_len,
				   loff_t pos, u64 ino, unsigned type)
{
	struct ocfs2_empty_dir_priv *p = priv;

	/*
	 * Check the positions of "." and ".." records to be sure
	 * they're in the correct place.
	 *
	 * Indexed directories don't need to proceed past the first
	 * two entries, so we end the scan after seeing '..'. Despite
	 * that, we allow the scan to proceed In the event that we
	 * have a corrupted indexed directory (no dot or dot dot
	 * entries). This allows us to double check for existing
	 * entries which might not have been found in the index.
	 */
	if (name_len == 1 && !strncmp(".", name, 1) && pos == 0) {
		p->seen_dot = 1;
		return 0;
	}

	if (name_len == 2 && !strncmp("..", name, 2) &&
	    pos == OCFS2_DIR_REC_LEN(1)) {
		p->seen_dot_dot = 1;

		if (p->dx_dir && p->seen_dot)
			return 1;

		return 0;
	}

	p->seen_other = 1;
	return 1;
}