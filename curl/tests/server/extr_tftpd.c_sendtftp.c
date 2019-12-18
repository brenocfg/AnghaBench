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
struct tftphdr {scalar_t__ th_opcode; unsigned short th_block; } ;
struct testcase {int writedelay; } ;
struct formats {int /*<<< orphan*/  f_convert; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/ * storage; struct tftphdr hdr; } ;

/* Variables and functions */
 int SEGSIZE ; 
 int /*<<< orphan*/  SIGALRM ; 
 TYPE_1__ ackbuf ; 
 int /*<<< orphan*/  alarm (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ got_exit_signal ; 
 void* htons (unsigned short volatile) ; 
 int /*<<< orphan*/  logmsg (char*,...) ; 
 int /*<<< orphan*/  mysignal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nak (scalar_t__) ; 
 void* ntohs (unsigned short) ; 
 scalar_t__ opcode_ACK ; 
 scalar_t__ opcode_DATA ; 
 scalar_t__ opcode_ERROR ; 
 int /*<<< orphan*/  peer ; 
 struct tftphdr* r_init () ; 
 int /*<<< orphan*/  read_ahead (struct testcase*,int /*<<< orphan*/ ) ; 
 int readit (struct testcase*,struct tftphdr**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rexmtval ; 
 int /*<<< orphan*/  sigsetjmp (int /*<<< orphan*/ ,int) ; 
 scalar_t__ sread (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int swrite (int /*<<< orphan*/ ,struct tftphdr* volatile,int) ; 
 int /*<<< orphan*/  synchnet (int /*<<< orphan*/ ) ; 
 scalar_t__ timeout ; 
 int /*<<< orphan*/  timeoutbuf ; 
 int /*<<< orphan*/  timer ; 
 int /*<<< orphan*/  wait_ms (int) ; 

__attribute__((used)) static void sendtftp(struct testcase *test, struct formats *pf)
{
  int size;
  ssize_t n;
  /* These are volatile to live through a siglongjmp */
  volatile unsigned short sendblock; /* block count */
  struct tftphdr * volatile sdp = r_init(); /* data buffer */
  struct tftphdr * const sap = &ackbuf.hdr; /* ack buffer */

  sendblock = 1;
#if defined(HAVE_ALARM) && defined(SIGALRM)
  mysignal(SIGALRM, timer);
#endif
  do {
    size = readit(test, (struct tftphdr **)&sdp, pf->f_convert);
    if(size < 0) {
      nak(errno + 100);
      return;
    }
    sdp->th_opcode = htons((unsigned short)opcode_DATA);
    sdp->th_block = htons(sendblock);
    timeout = 0;
#ifdef HAVE_SIGSETJMP
    (void) sigsetjmp(timeoutbuf, 1);
#endif
    if(test->writedelay) {
      logmsg("Pausing %d seconds before %d bytes", test->writedelay,
             size);
      wait_ms(1000*test->writedelay);
    }

    send_data:
    if(swrite(peer, sdp, size + 4) != size + 4) {
      logmsg("write");
      return;
    }
    read_ahead(test, pf->f_convert);
    for(;;) {
#ifdef HAVE_ALARM
      alarm(rexmtval);        /* read the ack */
#endif
      n = sread(peer, &ackbuf.storage[0], sizeof(ackbuf.storage));
#ifdef HAVE_ALARM
      alarm(0);
#endif
      if(got_exit_signal)
        return;
      if(n < 0) {
        logmsg("read: fail");
        return;
      }
      sap->th_opcode = ntohs((unsigned short)sap->th_opcode);
      sap->th_block = ntohs(sap->th_block);

      if(sap->th_opcode == opcode_ERROR) {
        logmsg("got ERROR");
        return;
      }

      if(sap->th_opcode == opcode_ACK) {
        if(sap->th_block == sendblock) {
          break;
        }
        /* Re-synchronize with the other side */
        (void) synchnet(peer);
        if(sap->th_block == (sendblock-1)) {
          goto send_data;
        }
      }

    }
    sendblock++;
  } while(size == SEGSIZE);
}