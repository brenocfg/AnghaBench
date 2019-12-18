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
struct ubi_vid_hdr {int dummy; } ;
struct ubi_device {int vid_hdr_shift; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static inline void ubi_free_vid_hdr(const struct ubi_device *ubi,
				    struct ubi_vid_hdr *vid_hdr)
{
	void *p = vid_hdr;

	if (!p)
		return;

	kfree(p - ubi->vid_hdr_shift);
}