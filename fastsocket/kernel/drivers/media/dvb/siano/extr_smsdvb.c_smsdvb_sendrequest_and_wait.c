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
struct smsdvb_client_t {int /*<<< orphan*/  smsclient; } ;
struct completion {int dummy; } ;
struct SmsMsgHdr_ST {int dummy; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int smsclient_sendrequest (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  smsendian_handle_tx_message (struct SmsMsgHdr_ST*) ; 
 scalar_t__ wait_for_completion_timeout (struct completion*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smsdvb_sendrequest_and_wait(struct smsdvb_client_t *client,
					void *buffer, size_t size,
					struct completion *completion)
{
	int rc;

	smsendian_handle_tx_message((struct SmsMsgHdr_ST *)buffer);
	rc = smsclient_sendrequest(client->smsclient, buffer, size);
	if (rc < 0)
		return rc;

	return wait_for_completion_timeout(completion,
					   msecs_to_jiffies(2000)) ?
						0 : -ETIME;
}