#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int response_code; } ;
struct write_sccb {TYPE_2__ header; } ;
struct sclp_req {scalar_t__ status; } ;
struct TYPE_3__ {void* status; } ;
struct sclp_buffer {int /*<<< orphan*/  (* callback ) (struct sclp_buffer*,int) ;TYPE_1__ request; int /*<<< orphan*/  retry_count; struct write_sccb* sccb; } ;
struct sccb_header {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SCLP_BUFFER_MAX_RETRY ; 
 scalar_t__ SCLP_REQ_FAILED ; 
 void* SCLP_REQ_FILLED ; 
 int sclp_add_request (struct sclp_req*) ; 
 int /*<<< orphan*/  sclp_remove_processed (struct sccb_header*) ; 
 int /*<<< orphan*/  stub1 (struct sclp_buffer*,int) ; 
 int /*<<< orphan*/  stub2 (struct sclp_buffer*,int) ; 

__attribute__((used)) static void
sclp_writedata_callback(struct sclp_req *request, void *data)
{
	int rc;
	struct sclp_buffer *buffer;
	struct write_sccb *sccb;

	buffer = (struct sclp_buffer *) data;
	sccb = buffer->sccb;

	if (request->status == SCLP_REQ_FAILED) {
		if (buffer->callback != NULL)
			buffer->callback(buffer, -EIO);
		return;
	}
	/* check SCLP response code and choose suitable action	*/
	switch (sccb->header.response_code) {
	case 0x0020 :
		/* Normal completion, buffer processed, message(s) sent */
		rc = 0;
		break;

	case 0x0340: /* Contained SCLP equipment check */
		if (++buffer->retry_count > SCLP_BUFFER_MAX_RETRY) {
			rc = -EIO;
			break;
		}
		/* remove processed buffers and requeue rest */
		if (sclp_remove_processed((struct sccb_header *) sccb) > 0) {
			/* not all buffers were processed */
			sccb->header.response_code = 0x0000;
			buffer->request.status = SCLP_REQ_FILLED;
			rc = sclp_add_request(request);
			if (rc == 0)
				return;
		} else
			rc = 0;
		break;

	case 0x0040: /* SCLP equipment check */
	case 0x05f0: /* Target resource in improper state */
		if (++buffer->retry_count > SCLP_BUFFER_MAX_RETRY) {
			rc = -EIO;
			break;
		}
		/* retry request */
		sccb->header.response_code = 0x0000;
		buffer->request.status = SCLP_REQ_FILLED;
		rc = sclp_add_request(request);
		if (rc == 0)
			return;
		break;
	default:
		if (sccb->header.response_code == 0x71f0)
			rc = -ENOMEM;
		else
			rc = -EINVAL;
		break;
	}
	if (buffer->callback != NULL)
		buffer->callback(buffer, rc);
}