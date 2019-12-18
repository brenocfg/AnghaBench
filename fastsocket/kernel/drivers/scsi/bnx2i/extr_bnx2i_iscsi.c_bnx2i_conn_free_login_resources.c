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
struct bnx2i_hba {TYPE_1__* pcidev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * req_buf; int /*<<< orphan*/  req_dma_addr; int /*<<< orphan*/ * resp_buf; int /*<<< orphan*/  resp_dma_addr; int /*<<< orphan*/ * req_bd_tbl; int /*<<< orphan*/  req_bd_dma; int /*<<< orphan*/ * resp_bd_tbl; int /*<<< orphan*/  resp_bd_dma; } ;
struct bnx2i_conn {TYPE_2__ gen_pdu; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_DEF_MAX_RECV_SEG_LEN ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2i_conn_free_login_resources(struct bnx2i_hba *hba,
					    struct bnx2i_conn *bnx2i_conn)
{
	if (bnx2i_conn->gen_pdu.resp_bd_tbl) {
		dma_free_coherent(&hba->pcidev->dev, PAGE_SIZE,
				  bnx2i_conn->gen_pdu.resp_bd_tbl,
				  bnx2i_conn->gen_pdu.resp_bd_dma);
		bnx2i_conn->gen_pdu.resp_bd_tbl = NULL;
	}

	if (bnx2i_conn->gen_pdu.req_bd_tbl) {
		dma_free_coherent(&hba->pcidev->dev, PAGE_SIZE,
				  bnx2i_conn->gen_pdu.req_bd_tbl,
				  bnx2i_conn->gen_pdu.req_bd_dma);
		bnx2i_conn->gen_pdu.req_bd_tbl = NULL;
	}

	if (bnx2i_conn->gen_pdu.resp_buf) {
		dma_free_coherent(&hba->pcidev->dev,
				  ISCSI_DEF_MAX_RECV_SEG_LEN,
				  bnx2i_conn->gen_pdu.resp_buf,
				  bnx2i_conn->gen_pdu.resp_dma_addr);
		bnx2i_conn->gen_pdu.resp_buf = NULL;
	}

	if (bnx2i_conn->gen_pdu.req_buf) {
		dma_free_coherent(&hba->pcidev->dev,
				  ISCSI_DEF_MAX_RECV_SEG_LEN,
				  bnx2i_conn->gen_pdu.req_buf,
				  bnx2i_conn->gen_pdu.req_dma_addr);
		bnx2i_conn->gen_pdu.req_buf = NULL;
	}
}