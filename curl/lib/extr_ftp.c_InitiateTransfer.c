#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pending_resp; } ;
struct TYPE_9__ {scalar_t__ state_saved; int retr_size_saved; TYPE_3__ pp; } ;
struct TYPE_10__ {TYPE_4__ ftpc; } ;
struct TYPE_6__ {scalar_t__ ftp_use_data_ssl; } ;
struct connectdata {TYPE_5__ proto; int /*<<< orphan*/ * sock; TYPE_1__ bits; struct Curl_easy* data; } ;
struct TYPE_7__ {int /*<<< orphan*/  infilesize; } ;
struct Curl_easy {TYPE_2__ state; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 int /*<<< orphan*/  Curl_pgrsSetUploadSize (struct Curl_easy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Curl_setup_transfer (struct Curl_easy*,size_t,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Curl_sndbufset (int /*<<< orphan*/ ) ; 
 scalar_t__ Curl_ssl_connect (struct connectdata*,size_t) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FTP_STOP ; 
 scalar_t__ FTP_STOR ; 
 size_t SECONDARYSOCKET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*) ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode InitiateTransfer(struct connectdata *conn)
{
  struct Curl_easy *data = conn->data;
  CURLcode result = CURLE_OK;

  if(conn->bits.ftp_use_data_ssl) {
    /* since we only have a plaintext TCP connection here, we must now
     * do the TLS stuff */
    infof(data, "Doing the SSL/TLS handshake on the data stream\n");
    result = Curl_ssl_connect(conn, SECONDARYSOCKET);
    if(result)
      return result;
  }

  if(conn->proto.ftpc.state_saved == FTP_STOR) {
    /* When we know we're uploading a specified file, we can get the file
       size prior to the actual upload. */
    Curl_pgrsSetUploadSize(data, data->state.infilesize);

    /* set the SO_SNDBUF for the secondary socket for those who need it */
    Curl_sndbufset(conn->sock[SECONDARYSOCKET]);

    Curl_setup_transfer(data, -1, -1, FALSE, SECONDARYSOCKET);
  }
  else {
    /* FTP download: */
    Curl_setup_transfer(data, SECONDARYSOCKET,
                        conn->proto.ftpc.retr_size_saved, FALSE, -1);
  }

  conn->proto.ftpc.pp.pending_resp = TRUE; /* expect server response */
  state(conn, FTP_STOP);

  return CURLE_OK;
}