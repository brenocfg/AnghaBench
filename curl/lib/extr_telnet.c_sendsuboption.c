#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct connectdata {int /*<<< orphan*/ * sock; struct Curl_easy* data; } ;
struct TELNET {scalar_t__ subbuffer; int /*<<< orphan*/  subopt_wsy; int /*<<< orphan*/  subopt_wsx; } ;
struct TYPE_2__ {scalar_t__ protop; } ;
struct Curl_easy {TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 unsigned char CURL_IAC ; 
 unsigned char CURL_SB ; 
 int /*<<< orphan*/  CURL_SB_ACCUM (struct TELNET*,int const) ; 
 int /*<<< orphan*/  CURL_SB_CLEAR (struct TELNET*) ; 
 int /*<<< orphan*/  CURL_SB_LEN (struct TELNET*) ; 
 int /*<<< orphan*/  CURL_SB_TERM (struct TELNET*) ; 
 unsigned char CURL_SE ; 
#define  CURL_TELOPT_NAWS 128 
 size_t FIRSTSOCKET ; 
 int SOCKERRNO ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*,int) ; 
 unsigned short htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printsub (struct Curl_easy*,char,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_telnet_data (struct connectdata*,char*,int) ; 
 int /*<<< orphan*/  swrite (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void sendsuboption(struct connectdata *conn, int option)
{
  ssize_t bytes_written;
  int err;
  unsigned short x, y;
  unsigned char *uc1, *uc2;

  struct Curl_easy *data = conn->data;
  struct TELNET *tn = (struct TELNET *)data->req.protop;

  switch(option) {
  case CURL_TELOPT_NAWS:
    /* We prepare data to be sent */
    CURL_SB_CLEAR(tn);
    CURL_SB_ACCUM(tn, CURL_IAC);
    CURL_SB_ACCUM(tn, CURL_SB);
    CURL_SB_ACCUM(tn, CURL_TELOPT_NAWS);
    /* We must deal either with little or big endian processors */
    /* Window size must be sent according to the 'network order' */
    x = htons(tn->subopt_wsx);
    y = htons(tn->subopt_wsy);
    uc1 = (unsigned char *)&x;
    uc2 = (unsigned char *)&y;
    CURL_SB_ACCUM(tn, uc1[0]);
    CURL_SB_ACCUM(tn, uc1[1]);
    CURL_SB_ACCUM(tn, uc2[0]);
    CURL_SB_ACCUM(tn, uc2[1]);

    CURL_SB_ACCUM(tn, CURL_IAC);
    CURL_SB_ACCUM(tn, CURL_SE);
    CURL_SB_TERM(tn);
    /* data suboption is now ready */

    printsub(data, '>', (unsigned char *)tn->subbuffer + 2,
             CURL_SB_LEN(tn)-2);

    /* we send the header of the suboption... */
    bytes_written = swrite(conn->sock[FIRSTSOCKET], tn->subbuffer, 3);
    if(bytes_written < 0) {
      err = SOCKERRNO;
      failf(data, "Sending data failed (%d)", err);
    }
    /* ... then the window size with the send_telnet_data() function
       to deal with 0xFF cases ... */
    send_telnet_data(conn, (char *)tn->subbuffer + 3, 4);
    /* ... and the footer */
    bytes_written = swrite(conn->sock[FIRSTSOCKET], tn->subbuffer + 7, 2);
    if(bytes_written < 0) {
      err = SOCKERRNO;
      failf(data, "Sending data failed (%d)", err);
    }
    break;
  }
}