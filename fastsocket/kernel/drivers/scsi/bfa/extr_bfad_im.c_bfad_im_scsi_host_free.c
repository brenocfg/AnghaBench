#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bfad_s {int /*<<< orphan*/  inst_no; } ;
struct bfad_im_port_s {int /*<<< orphan*/  idr_id; TYPE_1__* shost; } ;
struct TYPE_4__ {int /*<<< orphan*/  host_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_LOG (int /*<<< orphan*/ ,struct bfad_s*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  bfa_log_level ; 
 int /*<<< orphan*/  bfa_trc (struct bfad_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfad_im_port_index ; 
 int /*<<< orphan*/  bfad_mutex ; 
 int /*<<< orphan*/  fc_remove_host (TYPE_1__*) ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scsi_host_put (TYPE_1__*) ; 
 int /*<<< orphan*/  scsi_remove_host (TYPE_1__*) ; 

void
bfad_im_scsi_host_free(struct bfad_s *bfad, struct bfad_im_port_s *im_port)
{
	bfa_trc(bfad, bfad->inst_no);
	BFA_LOG(KERN_INFO, bfad, bfa_log_level, "Free scsi%d\n",
			im_port->shost->host_no);

	fc_remove_host(im_port->shost);

	scsi_remove_host(im_port->shost);
	scsi_host_put(im_port->shost);

	mutex_lock(&bfad_mutex);
	idr_remove(&bfad_im_port_index, im_port->idr_id);
	mutex_unlock(&bfad_mutex);
}