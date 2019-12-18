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
struct find_path_data {int /*<<< orphan*/  index; int /*<<< orphan*/  path; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  ocfs2_path_insert_eb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head*) ; 

__attribute__((used)) static void find_path_ins(void *data, struct buffer_head *bh)
{
	struct find_path_data *fp = data;

	get_bh(bh);
	ocfs2_path_insert_eb(fp->path, fp->index, bh);
	fp->index++;
}