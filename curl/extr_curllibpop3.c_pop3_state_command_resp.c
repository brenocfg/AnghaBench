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
struct pingpong {scalar_t__ cache_size; scalar_t__ cache; } ;
struct pop3_conn {int eob; int strip; struct pingpong pp; } ;
struct TYPE_5__ {struct pop3_conn pop3c; } ;
struct connectdata {TYPE_2__ proto; struct Curl_easy* data; } ;
struct POP3 {scalar_t__ transfer; } ;
struct TYPE_6__ {int /*<<< orphan*/  opt_no_body; } ;
struct TYPE_4__ {struct POP3* protop; } ;
struct Curl_easy {TYPE_3__ set; TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  pop3state ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLE_RECV_ERROR ; 
 scalar_t__ Curl_pop3_write (struct connectdata*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  Curl_safefree (scalar_t__) ; 
 int /*<<< orphan*/  Curl_setup_transfer (struct Curl_easy*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIRSTSOCKET ; 
 scalar_t__ FTPTRANSFER_BODY ; 
 int /*<<< orphan*/  POP3_STOP ; 
 int /*<<< orphan*/  state (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode pop3_state_command_resp(struct connectdata *conn,
                                        int pop3code,
                                        pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct POP3 *pop3 = data->req.protop;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  struct pingpong *pp = &pop3c->pp;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    state(conn, POP3_STOP);
    return CURLE_RECV_ERROR;
  }

  /* This 'OK' line ends with a CR LF pair which is the two first bytes of the
     EOB string so count this is two matching bytes. This is necessary to make
     the code detect the EOB if the only data than comes now is %2e CR LF like
     when there is no body to return. */
  pop3c->eob = 2;

  /* But since this initial CR LF pair is not part of the actual body, we set
     the strip counter here so that these bytes won't be delivered. */
  pop3c->strip = 2;

  if(pop3->transfer == FTPTRANSFER_BODY) {
    /* POP3 download */
    Curl_setup_transfer(data, FIRSTSOCKET, -1, FALSE, -1);

    if(pp->cache) {
      /* The header "cache" contains a bunch of data that is actually body
         content so send it as such. Note that there may even be additional
         "headers" after the body */

      if(!data->set.opt_no_body) {
        result = Curl_pop3_write(conn, pp->cache, pp->cache_size);
        if(result)
          return result;
      }

      /* Free the cache */
      Curl_safefree(pp->cache);

      /* Reset the cache size */
      pp->cache_size = 0;
    }
  }

  /* End of DO phase */
  state(conn, POP3_STOP);

  return result;
}