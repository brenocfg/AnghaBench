#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ftp_conn {scalar_t__ count1; void* wait_data_conn; int /*<<< orphan*/  file; void* dont_check; scalar_t__ state; } ;
struct TYPE_6__ {scalar_t__ httpproxy; scalar_t__ tunnel_proxy; int /*<<< orphan*/ * tcpconnect; } ;
struct TYPE_5__ {struct ftp_conn ftpc; } ;
struct connectdata {TYPE_2__ bits; TYPE_1__ proto; struct Curl_easy* data; } ;
struct FTP {scalar_t__ transfer; int downloadsize; } ;
struct TYPE_8__ {void* prefer_ascii; scalar_t__ ftp_list_only; scalar_t__ upload; } ;
struct TYPE_7__ {scalar_t__ maxdownload; struct FTP* protop; } ;
struct Curl_easy {TYPE_4__ set; TYPE_3__ req; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ AcceptServerConnect (struct connectdata*) ; 
 scalar_t__ CONNECT_SECONDARYSOCKET_PROXY_SSL () ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ Curl_connect_ongoing (struct connectdata*) ; 
 scalar_t__ Curl_is_connected (struct connectdata*,size_t,int*) ; 
 scalar_t__ Curl_proxyCONNECT (struct connectdata*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ Curl_proxy_connect (struct connectdata*,size_t) ; 
 scalar_t__ Curl_range (struct connectdata*) ; 
 int /*<<< orphan*/  Curl_setup_transfer (struct Curl_easy*,int,int,void*,int) ; 
 int /*<<< orphan*/  DEBUGF (int /*<<< orphan*/ ) ; 
 void* FALSE ; 
 scalar_t__ FTPTRANSFER_BODY ; 
 scalar_t__ FTPTRANSFER_INFO ; 
 int /*<<< orphan*/  FTP_LIST_TYPE ; 
 int /*<<< orphan*/  FTP_RETR_TYPE ; 
 int /*<<< orphan*/  FTP_STOR_TYPE ; 
 scalar_t__ InitiateTransfer (struct connectdata*) ; 
 scalar_t__ ReceivedServerConnect (struct connectdata*,int*) ; 
 size_t SECONDARYSOCKET ; 
 void* TRUE ; 
 scalar_t__ ftp_epsv_disable (struct connectdata*) ; 
 scalar_t__ ftp_multi_statemach (struct connectdata*,int*) ; 
 scalar_t__ ftp_nb_type (struct connectdata*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*,...) ; 

__attribute__((used)) static CURLcode ftp_do_more(struct connectdata *conn, int *completep)
{
  struct Curl_easy *data = conn->data;
  struct ftp_conn *ftpc = &conn->proto.ftpc;
  CURLcode result = CURLE_OK;
  bool connected = FALSE;
  bool complete = FALSE;

  /* the ftp struct is inited in ftp_connect() */
  struct FTP *ftp = data->req.protop;

  /* if the second connection isn't done yet, wait for it */
  if(!conn->bits.tcpconnect[SECONDARYSOCKET]) {
    if(Curl_connect_ongoing(conn)) {
      /* As we're in TUNNEL_CONNECT state now, we know the proxy name and port
         aren't used so we blank their arguments. */
      result = Curl_proxyCONNECT(conn, SECONDARYSOCKET, NULL, 0);

      return result;
    }

    result = Curl_is_connected(conn, SECONDARYSOCKET, &connected);

    /* Ready to do more? */
    if(connected) {
      DEBUGF(infof(data, "DO-MORE connected phase starts\n"));
    }
    else {
      if(result && (ftpc->count1 == 0)) {
        *completep = -1; /* go back to DOING please */
        /* this is a EPSV connect failing, try PASV instead */
        return ftp_epsv_disable(conn);
      }
      return result;
    }
  }

  result = Curl_proxy_connect(conn, SECONDARYSOCKET);
  if(result)
    return result;

  if(CONNECT_SECONDARYSOCKET_PROXY_SSL())
    return result;

  if(conn->bits.tunnel_proxy && conn->bits.httpproxy &&
     Curl_connect_ongoing(conn))
    return result;


  if(ftpc->state) {
    /* already in a state so skip the initial commands.
       They are only done to kickstart the do_more state */
    result = ftp_multi_statemach(conn, &complete);

    *completep = (int)complete;

    /* if we got an error or if we don't wait for a data connection return
       immediately */
    if(result || !ftpc->wait_data_conn)
      return result;

    /* if we reach the end of the FTP state machine here, *complete will be
       TRUE but so is ftpc->wait_data_conn, which says we need to wait for the
       data connection and therefore we're not actually complete */
    *completep = 0;
  }

  if(ftp->transfer <= FTPTRANSFER_INFO) {
    /* a transfer is about to take place, or if not a file name was given
       so we'll do a SIZE on it later and then we need the right TYPE first */

    if(ftpc->wait_data_conn == TRUE) {
      bool serv_conned;

      result = ReceivedServerConnect(conn, &serv_conned);
      if(result)
        return result; /* Failed to accept data connection */

      if(serv_conned) {
        /* It looks data connection is established */
        result = AcceptServerConnect(conn);
        ftpc->wait_data_conn = FALSE;
        if(!result)
          result = InitiateTransfer(conn);

        if(result)
          return result;

        *completep = 1; /* this state is now complete when the server has
                           connected back to us */
      }
    }
    else if(data->set.upload) {
      result = ftp_nb_type(conn, data->set.prefer_ascii, FTP_STOR_TYPE);
      if(result)
        return result;

      result = ftp_multi_statemach(conn, &complete);
      /* ftpc->wait_data_conn is always false here */
      *completep = (int)complete;
    }
    else {
      /* download */
      ftp->downloadsize = -1; /* unknown as of yet */

      result = Curl_range(conn);

      if(result == CURLE_OK && data->req.maxdownload >= 0) {
        /* Don't check for successful transfer */
        ftpc->dont_check = TRUE;
      }

      if(result)
        ;
      else if(data->set.ftp_list_only || !ftpc->file) {
        /* The specified path ends with a slash, and therefore we think this
           is a directory that is requested, use LIST. But before that we
           need to set ASCII transfer mode. */

        /* But only if a body transfer was requested. */
        if(ftp->transfer == FTPTRANSFER_BODY) {
          result = ftp_nb_type(conn, TRUE, FTP_LIST_TYPE);
          if(result)
            return result;
        }
        /* otherwise just fall through */
      }
      else {
        result = ftp_nb_type(conn, data->set.prefer_ascii, FTP_RETR_TYPE);
        if(result)
          return result;
      }

      result = ftp_multi_statemach(conn, &complete);
      *completep = (int)complete;
    }
    return result;
  }

  /* no data to transfer */
  Curl_setup_transfer(data, -1, -1, FALSE, -1);

  if(!ftpc->wait_data_conn) {
    /* no waiting for the data connection so this is now complete */
    *completep = 1;
    DEBUGF(infof(data, "DO-MORE phase ends with %d\n", (int)result));
  }

  return result;
}