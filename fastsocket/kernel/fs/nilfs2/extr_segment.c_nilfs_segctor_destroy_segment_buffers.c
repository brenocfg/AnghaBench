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
struct nilfs_segment_buffer {int /*<<< orphan*/  sb_list; } ;
struct nilfs_sc_info {int /*<<< orphan*/  sc_segbufs; } ;

/* Variables and functions */
 struct nilfs_segment_buffer* NILFS_FIRST_SEGBUF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_segbuf_free (struct nilfs_segment_buffer*) ; 

__attribute__((used)) static void nilfs_segctor_destroy_segment_buffers(struct nilfs_sc_info *sci)
{
	struct nilfs_segment_buffer *segbuf;

	while (!list_empty(&sci->sc_segbufs)) {
		segbuf = NILFS_FIRST_SEGBUF(&sci->sc_segbufs);
		list_del_init(&segbuf->sb_list);
		nilfs_segbuf_free(segbuf);
	}
	/* sci->sc_curseg = NULL; */
}