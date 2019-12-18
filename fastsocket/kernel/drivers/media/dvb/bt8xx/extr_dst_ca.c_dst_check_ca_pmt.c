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
struct dst_state {int dummy; } ;
struct ca_msg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DST_CA_ERROR ; 
 int /*<<< orphan*/  DST_CA_NOTICE ; 
 int /*<<< orphan*/  GET_REPLY ; 
 int /*<<< orphan*/  NO_REPLY ; 
 scalar_t__ ca_set_pmt (struct dst_state*,struct ca_msg*,struct ca_msg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  verbose ; 

__attribute__((used)) static int dst_check_ca_pmt(struct dst_state *state, struct ca_msg *p_ca_message, struct ca_msg *hw_buffer)
{
	int ca_pmt_reply_test = 0;

	/*	Do test board			*/
	/*	Not there yet but soon		*/

	/*	CA PMT Reply capable		*/
	if (ca_pmt_reply_test) {
		if ((ca_set_pmt(state, p_ca_message, hw_buffer, 1, GET_REPLY)) < 0) {
			dprintk(verbose, DST_CA_ERROR, 1, " ca_set_pmt.. failed !");
			return -1;
		}

	/*	Process CA PMT Reply		*/
	/*	will implement soon		*/
		dprintk(verbose, DST_CA_ERROR, 1, " Not there yet");
	}
	/*	CA PMT Reply not capable	*/
	if (!ca_pmt_reply_test) {
		if ((ca_set_pmt(state, p_ca_message, hw_buffer, 0, NO_REPLY)) < 0) {
			dprintk(verbose, DST_CA_ERROR, 1, " ca_set_pmt.. failed !");
			return -1;
		}
		dprintk(verbose, DST_CA_NOTICE, 1, " ca_set_pmt.. success !");
	/*	put a dummy message		*/

	}
	return 0;
}