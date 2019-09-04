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
struct connectdata {struct Curl_easy* data; } ;
struct TELNET {int telrcv_state; int please_negotiate; int subpointer; } ;
struct TYPE_2__ {scalar_t__ protop; } ;
struct Curl_easy {TYPE_1__ req; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENTWRITE_BODY ; 
 scalar_t__ CURLE_OK ; 
#define  CURL_DM 145 
#define  CURL_DO 144 
#define  CURL_DONT 143 
#define  CURL_GA 142 
#define  CURL_IAC 141 
#define  CURL_NOP 140 
#define  CURL_SB 139 
 int /*<<< orphan*/  CURL_SB_ACCUM (struct TELNET*,unsigned char) ; 
 int /*<<< orphan*/  CURL_SB_CLEAR (struct TELNET*) ; 
 int /*<<< orphan*/  CURL_SB_TERM (struct TELNET*) ; 
 unsigned char CURL_SE ; 
#define  CURL_TS_CR 138 
#define  CURL_TS_DATA 137 
#define  CURL_TS_DO 136 
#define  CURL_TS_DONT 135 
#define  CURL_TS_IAC 134 
#define  CURL_TS_SB 133 
#define  CURL_TS_SE 132 
#define  CURL_TS_WILL 131 
#define  CURL_TS_WONT 130 
#define  CURL_WILL 129 
#define  CURL_WONT 128 
 scalar_t__ Curl_client_write (struct connectdata*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DEBUGASSERT (int) ; 
 int /*<<< orphan*/  printoption (struct Curl_easy*,char*,unsigned char const,unsigned char) ; 
 int /*<<< orphan*/  rec_do (struct connectdata*,unsigned char) ; 
 int /*<<< orphan*/  rec_dont (struct connectdata*,unsigned char) ; 
 int /*<<< orphan*/  rec_will (struct connectdata*,unsigned char) ; 
 int /*<<< orphan*/  rec_wont (struct connectdata*,unsigned char) ; 
 int /*<<< orphan*/  suboption (struct connectdata*) ; 

__attribute__((used)) static
CURLcode telrcv(struct connectdata *conn,
                const unsigned char *inbuf, /* Data received from socket */
                ssize_t count)              /* Number of bytes received */
{
  unsigned char c;
  CURLcode result;
  int in = 0;
  int startwrite = -1;
  struct Curl_easy *data = conn->data;
  struct TELNET *tn = (struct TELNET *)data->req.protop;

#define startskipping()                                       \
  if(startwrite >= 0) {                                       \
    result = Curl_client_write(conn,                          \
                               CLIENTWRITE_BODY,              \
                               (char *)&inbuf[startwrite],    \
                               in-startwrite);                \
    if(result)                                                \
      return result;                                          \
  }                                                           \
  startwrite = -1

#define writebyte() \
    if(startwrite < 0) \
      startwrite = in

#define bufferflush() startskipping()

  while(count--) {
    c = inbuf[in];

    switch(tn->telrcv_state) {
    case CURL_TS_CR:
      tn->telrcv_state = CURL_TS_DATA;
      if(c == '\0') {
        startskipping();
        break;   /* Ignore \0 after CR */
      }
      writebyte();
      break;

    case CURL_TS_DATA:
      if(c == CURL_IAC) {
        tn->telrcv_state = CURL_TS_IAC;
        startskipping();
        break;
      }
      else if(c == '\r')
        tn->telrcv_state = CURL_TS_CR;
      writebyte();
      break;

    case CURL_TS_IAC:
    process_iac:
      DEBUGASSERT(startwrite < 0);
      switch(c) {
      case CURL_WILL:
        tn->telrcv_state = CURL_TS_WILL;
        break;
      case CURL_WONT:
        tn->telrcv_state = CURL_TS_WONT;
        break;
      case CURL_DO:
        tn->telrcv_state = CURL_TS_DO;
        break;
      case CURL_DONT:
        tn->telrcv_state = CURL_TS_DONT;
        break;
      case CURL_SB:
        CURL_SB_CLEAR(tn);
        tn->telrcv_state = CURL_TS_SB;
        break;
      case CURL_IAC:
        tn->telrcv_state = CURL_TS_DATA;
        writebyte();
        break;
      case CURL_DM:
      case CURL_NOP:
      case CURL_GA:
      default:
        tn->telrcv_state = CURL_TS_DATA;
        printoption(data, "RCVD", CURL_IAC, c);
        break;
      }
      break;

      case CURL_TS_WILL:
        printoption(data, "RCVD", CURL_WILL, c);
        tn->please_negotiate = 1;
        rec_will(conn, c);
        tn->telrcv_state = CURL_TS_DATA;
        break;

      case CURL_TS_WONT:
        printoption(data, "RCVD", CURL_WONT, c);
        tn->please_negotiate = 1;
        rec_wont(conn, c);
        tn->telrcv_state = CURL_TS_DATA;
        break;

      case CURL_TS_DO:
        printoption(data, "RCVD", CURL_DO, c);
        tn->please_negotiate = 1;
        rec_do(conn, c);
        tn->telrcv_state = CURL_TS_DATA;
        break;

      case CURL_TS_DONT:
        printoption(data, "RCVD", CURL_DONT, c);
        tn->please_negotiate = 1;
        rec_dont(conn, c);
        tn->telrcv_state = CURL_TS_DATA;
        break;

      case CURL_TS_SB:
        if(c == CURL_IAC)
          tn->telrcv_state = CURL_TS_SE;
        else
          CURL_SB_ACCUM(tn, c);
        break;

      case CURL_TS_SE:
        if(c != CURL_SE) {
          if(c != CURL_IAC) {
            /*
             * This is an error.  We only expect to get "IAC IAC" or "IAC SE".
             * Several things may have happened.  An IAC was not doubled, the
             * IAC SE was left off, or another option got inserted into the
             * suboption are all possibilities.  If we assume that the IAC was
             * not doubled, and really the IAC SE was left off, we could get
             * into an infinite loop here.  So, instead, we terminate the
             * suboption, and process the partial suboption if we can.
             */
            CURL_SB_ACCUM(tn, CURL_IAC);
            CURL_SB_ACCUM(tn, c);
            tn->subpointer -= 2;
            CURL_SB_TERM(tn);

            printoption(data, "In SUBOPTION processing, RCVD", CURL_IAC, c);
            suboption(conn);   /* handle sub-option */
            tn->telrcv_state = CURL_TS_IAC;
            goto process_iac;
          }
          CURL_SB_ACCUM(tn, c);
          tn->telrcv_state = CURL_TS_SB;
        }
        else {
          CURL_SB_ACCUM(tn, CURL_IAC);
          CURL_SB_ACCUM(tn, CURL_SE);
          tn->subpointer -= 2;
          CURL_SB_TERM(tn);
          suboption(conn);   /* handle sub-option */
          tn->telrcv_state = CURL_TS_DATA;
        }
        break;
    }
    ++in;
  }
  bufferflush();
  return CURLE_OK;
}