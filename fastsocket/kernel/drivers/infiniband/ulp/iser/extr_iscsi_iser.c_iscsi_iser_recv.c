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
struct iscsi_hdr {int hlength; int /*<<< orphan*/  dlength; } ;
struct iscsi_conn {int dummy; } ;

/* Variables and functions */
 int ISCSI_ERR_DATALEN ; 
 int ISCSI_ERR_NO_SCSI_CMD ; 
 int iscsi_complete_pdu (struct iscsi_conn*,struct iscsi_hdr*,char*,int) ; 
 int /*<<< orphan*/  iscsi_conn_failure (struct iscsi_conn*,int) ; 
 int /*<<< orphan*/  iser_dbg (char*,int,int) ; 
 int /*<<< orphan*/  iser_err (char*,int,int) ; 
 int ntoh24 (int /*<<< orphan*/ ) ; 

void
iscsi_iser_recv(struct iscsi_conn *conn,
		struct iscsi_hdr *hdr, char *rx_data, int rx_data_len)
{
	int rc = 0;
	int datalen;
	int ahslen;

	/* verify PDU length */
	datalen = ntoh24(hdr->dlength);
	if (datalen > rx_data_len || (datalen + 4) < rx_data_len) {
		iser_err("wrong datalen %d (hdr), %d (IB)\n",
			datalen, rx_data_len);
		rc = ISCSI_ERR_DATALEN;
		goto error;
	}

	if (datalen != rx_data_len)
		iser_dbg("aligned datalen (%d) hdr, %d (IB)\n",
			datalen, rx_data_len);

	/* read AHS */
	ahslen = hdr->hlength * 4;

	rc = iscsi_complete_pdu(conn, hdr, rx_data, rx_data_len);
	if (rc && rc != ISCSI_ERR_NO_SCSI_CMD)
		goto error;

	return;
error:
	iscsi_conn_failure(conn, rc);
}