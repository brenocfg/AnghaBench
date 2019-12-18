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
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ u32 ;
struct fc_rport {scalar_t__ dev_loss_tmo; struct bfad_itnim_data_s* dd_data; } ;
struct bfad_s {int /*<<< orphan*/  bfa; } ;
struct bfad_itnim_s {TYPE_1__* im; } ;
struct bfad_itnim_data_s {struct bfad_itnim_s* itnim; } ;
struct TYPE_2__ {struct bfad_s* bfad; } ;

/* Variables and functions */
 scalar_t__ bfa_fcpim_path_tov_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfad_im_set_rport_loss_tmo(struct fc_rport *rport, u32 timeout)
{
	struct bfad_itnim_data_s *itnim_data = rport->dd_data;
	struct bfad_itnim_s   *itnim = itnim_data->itnim;
	struct bfad_s         *bfad = itnim->im->bfad;
	uint16_t path_tov = bfa_fcpim_path_tov_get(&bfad->bfa);

	rport->dev_loss_tmo = timeout;
	if (timeout < path_tov)
		rport->dev_loss_tmo = path_tov + 1;
}