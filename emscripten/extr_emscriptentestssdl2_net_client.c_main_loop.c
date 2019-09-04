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
struct TYPE_2__ {size_t msg_i; scalar_t__ msg_state; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 scalar_t__ MSG_READ ; 
 scalar_t__ MSG_WRITE ; 
 char* SDLNet_GetError () ; 
 int SDLNet_TCP_Recv (int /*<<< orphan*/ ,void*,int) ; 
 int SDLNet_TCP_Send (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int /*<<< orphan*/  finish (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,char*) ; 
 char** msgs ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__ state ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strlen (char*) ; 

void main_loop()
{
  char *sendbuf = msgs[state.msg_i];
  char recvbuf[256] = {0};
  int actual = 0, len = strlen(sendbuf) + 1;
  printf("main loop with string %s and len %d\n", sendbuf, len);

  if (state.msg_state == MSG_WRITE) {
    printf("trying to send %s\n", sendbuf);
    if ((actual = SDLNet_TCP_Send(state.sd, (void *)sendbuf, len)) != len)
    {
      fprintf(stderr, "SDLNet_TCP_Send: count:%d/%d errno:%d msg:%s\n",
        actual, len, errno, SDLNet_GetError());
      if (errno == EAGAIN) {
        if (actual > 0) {
          assert(0);
        }
        return;
      }
      finish(EXIT_FAILURE);
    }
    printf("send success\n");
    state.msg_state = MSG_READ;
  }
  if (state.msg_state == MSG_READ) {
    printf("trying to receive %s\n", sendbuf);
    if ((actual = SDLNet_TCP_Recv(state.sd, (void *)recvbuf, len)) != len)
    {
      fprintf(stderr, "SDLNet_TCP_Recv: count:%d/%d errno:%d msg:%s\n",
        actual, len, errno, SDLNet_GetError());
      if (errno == EAGAIN) {
        if (actual > 0) {
          assert(0);
        }
        return;
      }
      finish(EXIT_FAILURE);
    }
    printf("receive success\n");
    assert(strcmp(sendbuf, recvbuf) == 0);
    if (!strcmp(recvbuf, "exit")) {
      finish(EXIT_SUCCESS);
    }
    state.msg_i++;
    state.msg_state = MSG_WRITE;
  }
}