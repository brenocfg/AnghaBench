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
struct virtio_scsi_target_state {struct scatterlist* sg; } ;
struct virtio_scsi_cmd {int /*<<< orphan*/  resp; int /*<<< orphan*/  req; struct scsi_cmnd* sc; } ;
struct scsi_cmnd {scalar_t__ sc_data_direction; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  scsi_in (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  scsi_out (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sg_set_buf (struct scatterlist*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  virtscsi_map_sgl (struct scatterlist*,unsigned int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void virtscsi_map_cmd(struct virtio_scsi_target_state *tgt,
			     struct virtio_scsi_cmd *cmd,
			     unsigned *out_num, unsigned *in_num,
			     size_t req_size, size_t resp_size)
{
	struct scsi_cmnd *sc = cmd->sc;
	struct scatterlist *sg = tgt->sg;
	unsigned int idx = 0;

	/* Request header.  */
	sg_set_buf(&sg[idx++], &cmd->req, req_size);

	/* Data-out buffer.  */
	if (sc && sc->sc_data_direction != DMA_FROM_DEVICE)
		virtscsi_map_sgl(sg, &idx, scsi_out(sc));

	*out_num = idx;

	/* Response header.  */
	sg_set_buf(&sg[idx++], &cmd->resp, resp_size);

	/* Data-in buffer */
	if (sc && sc->sc_data_direction != DMA_TO_DEVICE)
		virtscsi_map_sgl(sg, &idx, scsi_in(sc));

	*in_num = idx - *out_num;
}