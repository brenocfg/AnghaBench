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
struct pcf50633_adc_request {int mux; int avg; int result; int /*<<< orphan*/  completion; struct pcf50633_adc_request* callback_param; int /*<<< orphan*/  callback; } ;
struct pcf50633 {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int adc_enqueue_request (struct pcf50633*,struct pcf50633_adc_request*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct pcf50633_adc_request* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcf50633_adc_sync_read_callback ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int pcf50633_adc_sync_read(struct pcf50633 *pcf, int mux, int avg)
{
	struct pcf50633_adc_request *req;
	int err;

	/* req is freed when the result is ready, in interrupt handler */
	req = kzalloc(sizeof(*req), GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	req->mux = mux;
	req->avg = avg;
	req->callback =  pcf50633_adc_sync_read_callback;
	req->callback_param = req;

	init_completion(&req->completion);
	err = adc_enqueue_request(pcf, req);
	if (err)
		return err;

	wait_for_completion(&req->completion);

	/* FIXME by this time req might be already freed */
	return req->result;
}