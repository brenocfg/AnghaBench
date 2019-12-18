#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct qeth_reply {int dummy; } ;
struct qeth_cmd_buffer {scalar_t__ rc; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {scalar_t__ link_type; int /*<<< orphan*/  type; scalar_t__ max_mtu; scalar_t__ initial_mtu; } ;
struct TYPE_5__ {scalar_t__ in_buf_size; } ;
struct TYPE_4__ {scalar_t__ ulp_filter_r; } ;
struct qeth_card {TYPE_3__ info; TYPE_2__ qdio; TYPE_1__ token; } ;
typedef  scalar_t__ __u8 ;
typedef  scalar_t__ __u16 ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,scalar_t__) ; 
 scalar_t__ QETH_IN_BUF_SIZE_DEFAULT ; 
 scalar_t__ QETH_MPC_DIFINFO_LEN_INDICATES_LINK_TYPE ; 
 int QETH_MPC_TOKEN_LENGTH ; 
 int /*<<< orphan*/  QETH_ULP_ENABLE_RESP_DIFINFO_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_ULP_ENABLE_RESP_FILTER_TOKEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_ULP_ENABLE_RESP_LINK_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QETH_ULP_ENABLE_RESP_MAX_MTU (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ qeth_get_initial_mtu_for_card (struct qeth_card*) ; 
 scalar_t__ qeth_get_max_mtu_for_card (int /*<<< orphan*/ ) ; 
 scalar_t__ qeth_get_mtu_out_of_mpc (int /*<<< orphan*/ ) ; 
 scalar_t__ qeth_get_mtu_outof_framesize (scalar_t__) ; 

__attribute__((used)) static int qeth_ulp_enable_cb(struct qeth_card *card, struct qeth_reply *reply,
		unsigned long data)
{

	__u16 mtu, framesize;
	__u16 len;
	__u8 link_type;
	struct qeth_cmd_buffer *iob;

	QETH_DBF_TEXT(SETUP, 2, "ulpenacb");

	iob = (struct qeth_cmd_buffer *) data;
	memcpy(&card->token.ulp_filter_r,
	       QETH_ULP_ENABLE_RESP_FILTER_TOKEN(iob->data),
	       QETH_MPC_TOKEN_LENGTH);
	if (qeth_get_mtu_out_of_mpc(card->info.type)) {
		memcpy(&framesize, QETH_ULP_ENABLE_RESP_MAX_MTU(iob->data), 2);
		mtu = qeth_get_mtu_outof_framesize(framesize);
		if (!mtu) {
			iob->rc = -EINVAL;
			QETH_DBF_TEXT_(SETUP, 2, "  rc%d", iob->rc);
			return 0;
		}
		card->info.max_mtu = mtu;
		card->info.initial_mtu = mtu;
		card->qdio.in_buf_size = mtu + 2 * PAGE_SIZE;
	} else {
		card->info.initial_mtu = qeth_get_initial_mtu_for_card(card);
		card->info.max_mtu = qeth_get_max_mtu_for_card(card->info.type);
		card->qdio.in_buf_size = QETH_IN_BUF_SIZE_DEFAULT;
	}

	memcpy(&len, QETH_ULP_ENABLE_RESP_DIFINFO_LEN(iob->data), 2);
	if (len >= QETH_MPC_DIFINFO_LEN_INDICATES_LINK_TYPE) {
		memcpy(&link_type,
		       QETH_ULP_ENABLE_RESP_LINK_TYPE(iob->data), 1);
		card->info.link_type = link_type;
	} else
		card->info.link_type = 0;
	QETH_DBF_TEXT_(SETUP, 2, "link%d", link_type);
	QETH_DBF_TEXT_(SETUP, 2, "  rc%d", iob->rc);
	return 0;
}