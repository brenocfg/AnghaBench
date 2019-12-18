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
struct gfs2_sbd {int dummy; } ;
typedef  int /*<<< orphan*/  glock_examiner ;

/* Variables and functions */
 unsigned int GFS2_GL_HASH_SIZE ; 
 int /*<<< orphan*/  examine_bucket (int /*<<< orphan*/ ,struct gfs2_sbd const*,unsigned int) ; 

__attribute__((used)) static void glock_hash_walk(glock_examiner examiner, const struct gfs2_sbd *sdp)
{
	unsigned x;

	for (x = 0; x < GFS2_GL_HASH_SIZE; x++)
		examine_bucket(examiner, sdp, x);
}