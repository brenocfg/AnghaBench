#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct gfs2_statfs_change_host {int dummy; } ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_rgrpd {int /*<<< orphan*/  rd_gl; } ;
struct gfs2_holder {TYPE_1__* gh_gl; } ;
struct TYPE_2__ {int /*<<< orphan*/  gl_object; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GL_ASYNC ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 scalar_t__ gfs2_glock_poll (struct gfs2_holder*) ; 
 int gfs2_glock_wait (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_uninit (struct gfs2_holder*) ; 
 struct gfs2_rgrpd* gfs2_rgrpd_get_first (struct gfs2_sbd*) ; 
 struct gfs2_rgrpd* gfs2_rgrpd_get_next (struct gfs2_rgrpd*) ; 
 struct gfs2_holder* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gfs2_holder*) ; 
 int /*<<< orphan*/  memset (struct gfs2_statfs_change_host*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int statfs_slow_fill (int /*<<< orphan*/ ,struct gfs2_statfs_change_host*) ; 
 int /*<<< orphan*/  yield () ; 

__attribute__((used)) static int gfs2_statfs_slow(struct gfs2_sbd *sdp, struct gfs2_statfs_change_host *sc)
{
	struct gfs2_rgrpd *rgd_next;
	struct gfs2_holder *gha, *gh;
	unsigned int slots = 64;
	unsigned int x;
	int done;
	int error = 0, err;

	memset(sc, 0, sizeof(struct gfs2_statfs_change_host));
	gha = kcalloc(slots, sizeof(struct gfs2_holder), GFP_KERNEL);
	if (!gha)
		return -ENOMEM;

	rgd_next = gfs2_rgrpd_get_first(sdp);

	for (;;) {
		done = 1;

		for (x = 0; x < slots; x++) {
			gh = gha + x;

			if (gh->gh_gl && gfs2_glock_poll(gh)) {
				err = gfs2_glock_wait(gh);
				if (err) {
					gfs2_holder_uninit(gh);
					error = err;
				} else {
					if (!error)
						error = statfs_slow_fill(
							gh->gh_gl->gl_object, sc);
					gfs2_glock_dq_uninit(gh);
				}
			}

			if (gh->gh_gl)
				done = 0;
			else if (rgd_next && !error) {
				error = gfs2_glock_nq_init(rgd_next->rd_gl,
							   LM_ST_SHARED,
							   GL_ASYNC,
							   gh);
				rgd_next = gfs2_rgrpd_get_next(rgd_next);
				done = 0;
			}

			if (signal_pending(current))
				error = -ERESTARTSYS;
		}

		if (done)
			break;

		yield();
	}

	kfree(gha);
	return error;
}