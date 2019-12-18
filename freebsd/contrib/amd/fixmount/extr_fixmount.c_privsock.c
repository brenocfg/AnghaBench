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

/* Variables and functions */
 int RPC_ANYSOCK ; 
 scalar_t__ errno ; 
 int inetresport (int) ; 

__attribute__((used)) static int
privsock(int ty)
{
  int sock = inetresport(ty);

  if (sock < 0) {
    errno = 0;
    /* Couldn't get a secure port, let RPC make an insecure one */
    sock = RPC_ANYSOCK;
  }
  return sock;
}