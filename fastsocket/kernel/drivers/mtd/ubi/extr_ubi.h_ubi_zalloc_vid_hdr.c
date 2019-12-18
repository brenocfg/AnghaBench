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
typedef  void ubi_vid_hdr ;
struct ubi_device {int vid_hdr_shift; int /*<<< orphan*/  vid_hdr_alsize; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct ubi_vid_hdr *
ubi_zalloc_vid_hdr(const struct ubi_device *ubi, gfp_t gfp_flags)
{
	void *vid_hdr;

	vid_hdr = kzalloc(ubi->vid_hdr_alsize, gfp_flags);
	if (!vid_hdr)
		return NULL;

	/*
	 * VID headers may be stored at un-aligned flash offsets, so we shift
	 * the pointer.
	 */
	return vid_hdr + ubi->vid_hdr_shift;
}