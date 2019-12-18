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
struct tftphdr {int /*<<< orphan*/  th_msg; void* th_code; void* th_opcode; } ;
struct errmsg {int e_code; int /*<<< orphan*/  e_msg; } ;
struct TYPE_2__ {int /*<<< orphan*/ * storage; struct tftphdr hdr; } ;

/* Variables and functions */
 void* EUNDEF ; 
 TYPE_1__ buf ; 
 struct errmsg* errmsgs ; 
 void* htons (unsigned short) ; 
 int /*<<< orphan*/  logmsg (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ opcode_ERROR ; 
 int /*<<< orphan*/  peer ; 
 int /*<<< orphan*/  strerror (int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int swrite (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void nak(int error)
{
  struct tftphdr *tp;
  int length;
  struct errmsg *pe;

  tp = &buf.hdr;
  tp->th_opcode = htons((unsigned short)opcode_ERROR);
  tp->th_code = htons((unsigned short)error);
  for(pe = errmsgs; pe->e_code >= 0; pe++)
    if(pe->e_code == error)
      break;
  if(pe->e_code < 0) {
    pe->e_msg = strerror(error - 100);
    tp->th_code = EUNDEF;   /* set 'undef' errorcode */
  }
  length = (int)strlen(pe->e_msg);

  /* we use memcpy() instead of strcpy() in order to avoid buffer overflow
   * report from glibc with FORTIFY_SOURCE */
  memcpy(tp->th_msg, pe->e_msg, length + 1);
  length += 5;
  if(swrite(peer, &buf.storage[0], length) != length)
    logmsg("nak: fail\n");
}