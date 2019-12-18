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
struct scsi_cmnd {int /*<<< orphan*/ * cmnd; } ;
struct scatterlist {int /*<<< orphan*/  length; } ;
struct TYPE_2__ {int data_pipe; int /*<<< orphan*/  data_length; int /*<<< orphan*/ * data; scalar_t__ fragment; struct scsi_cmnd* srb; struct mts_desc* instance; } ;
struct mts_desc {TYPE_1__ context; scalar_t__ ep_out; int /*<<< orphan*/  usb_dev; scalar_t__ ep_response; scalar_t__ ep_image; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTS_DEBUG (char*,int) ; 
 int /*<<< orphan*/  MTS_DEBUG_GOT_HERE () ; 
 scalar_t__ MTS_DIRECTION_IS_IN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mts_read_image_sig ; 
 int /*<<< orphan*/  mts_read_image_sig_len ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 struct scatterlist* scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/ * sg_virt (struct scatterlist*) ; 
 int usb_rcvbulkpipe (int /*<<< orphan*/ ,scalar_t__) ; 
 int usb_sndbulkpipe (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
mts_build_transfer_context(struct scsi_cmnd *srb, struct mts_desc* desc)
{
	int pipe;
	struct scatterlist * sg;
	
	MTS_DEBUG_GOT_HERE();

	desc->context.instance = desc;
	desc->context.srb = srb;
	desc->context.fragment = 0;

	if (!scsi_bufflen(srb)) {
		desc->context.data = NULL;
		desc->context.data_length = 0;
		return;
	} else {
		sg = scsi_sglist(srb);
		desc->context.data = sg_virt(&sg[0]);
		desc->context.data_length = sg[0].length;
	}


	/* can't rely on srb->sc_data_direction */

	/* Brutally ripped from usb-storage */

	if ( !memcmp( srb->cmnd, mts_read_image_sig, mts_read_image_sig_len )
) { 		pipe = usb_rcvbulkpipe(desc->usb_dev,desc->ep_image);
		MTS_DEBUG( "transfering from desc->ep_image == %d\n",
			   (int)desc->ep_image );
	} else if ( MTS_DIRECTION_IS_IN(srb->cmnd[0]) ) {
			pipe = usb_rcvbulkpipe(desc->usb_dev,desc->ep_response);
			MTS_DEBUG( "transfering from desc->ep_response == %d\n",
				   (int)desc->ep_response);
	} else {
		MTS_DEBUG("transfering to desc->ep_out == %d\n",
			  (int)desc->ep_out);
		pipe = usb_sndbulkpipe(desc->usb_dev,desc->ep_out);
	}
	desc->context.data_pipe = pipe;
}