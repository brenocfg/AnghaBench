#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_6__ {int length; } ;
struct TYPE_5__ {int length; } ;

/* Variables and functions */
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  FD_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int do_msg_read (int /*<<< orphan*/ ,TYPE_2__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int do_msg_write (int /*<<< orphan*/ ,TYPE_1__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  finish (int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_2__ readmsg ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sockfd ; 
 TYPE_1__ writemsg ; 

void main_loop() {
  static int state = 0;
  static int readPos = 0;
  static int writePos = 0;
  int selectRes;
  ssize_t transferAmount;
  fd_set sett;  
  
  switch (state) {
    case 0:
      // writing 10 bytes to the server
      
      // since the socket in the read file descriptors has no available data,
      // select should tell us 0 handles are ready
      FD_ZERO(&sett);
      FD_SET(sockfd, &sett);
      selectRes = select(64, &sett, NULL, NULL, NULL);
      if (selectRes != 0) {
        printf("case 0: read select != 0 (%d)\n", selectRes);
        finish(EXIT_FAILURE);
      }
      
      // the socket in the write file descriptors has to result in either a 0 or 1
      // the connection either is setting up or is established and writing is possible
      FD_ZERO(&sett);
      FD_SET(sockfd, &sett);
      selectRes = select(64, NULL, &sett, NULL, NULL);
      if (selectRes == -1) {
        printf("case 0: write select == -1\n");
        finish(EXIT_FAILURE);
      } else if (selectRes == 0) {
        return;
      }
      
      // send a single byte
      transferAmount = do_msg_write(sockfd, &writemsg, writePos, 1, NULL, 0);
      if (transferAmount != -1) writePos += transferAmount;
   
      // after 10 bytes switch to next state
      if (writePos >= writemsg.length) {
        state = 1;
      }
      break;
      
    case 1:
      // wait until we can read one byte to make sure the server
      // has sent the data and then closed the connection
      FD_ZERO(&sett);
      FD_SET(sockfd, &sett);
      selectRes = select(64, &sett, NULL, NULL, NULL);
      if (selectRes == -1) {
        printf("case 1: read selectRes == -1\n");
        finish(EXIT_FAILURE);
      } else if (selectRes == 0) {
        return;
      }

      // read a single byte
      transferAmount = do_msg_read(sockfd, &readmsg, readPos, 1, NULL, NULL);
      if (transferAmount == 0) {
        perror("server closed");
        finish(EXIT_FAILURE);
      } else if (transferAmount != -1) {
        readPos += transferAmount;
      }
   
      // if successfully reading 1 byte, switch to next state
      if (readPos >= 1) {
        state = 2;
      }
      break;
    
    case 2:
      // calling select with the socket in the write file descriptors should
      // succeed, but the socket should not set in the set.
      FD_ZERO(&sett);
      FD_SET(sockfd, &sett);
      selectRes = select(64, NULL, &sett, NULL, NULL);
      if (selectRes != 0 || FD_ISSET(sockfd, &sett)) {
        printf("case 2: write selectRes != 0 || FD_ISSET(sockfd, &sett)\n");
        finish(EXIT_FAILURE);
      }

      // calling select with the socket in the read file descriptors 
      // has to succeed because there is still data in the inQueue
      FD_ZERO(&sett);
      FD_SET(sockfd, &sett);
      selectRes = select(64, &sett, NULL, NULL, NULL);
      if (selectRes != 1) {
        printf("case 2: read selectRes != 1\n");
        finish(EXIT_FAILURE);
      } else if (selectRes == 0) {
        return;
      }
      
      // read a single byte
      transferAmount = do_msg_read(sockfd, &readmsg, readPos, 1, NULL, NULL);
      if (transferAmount == 0) {
        perror("server closed");
        finish(EXIT_FAILURE);
      } else if (transferAmount != -1) {
        readPos += transferAmount;
      }
      
      // with 10 bytes read the inQueue is empty => switch state
      if (readPos >= readmsg.length) {
        state = 3;
      }
      break;
      
    case 3:
      // calling select with the socket in the read file descriptors 
      // should succeed
      FD_ZERO(&sett);
      FD_SET(sockfd, &sett);
      selectRes = select(64, &sett, NULL, NULL, NULL);
      if (selectRes != 1) {
        printf("case 3: read selectRes != 1\n");
        finish(EXIT_FAILURE);
      }

      // but recv should return 0 signaling the remote
      // end has closed the connection.
      transferAmount = do_msg_read(sockfd, &readmsg, readPos, 0, NULL, NULL);
      if (transferAmount) {
        printf("case 3: read != 0\n");
        finish(EXIT_FAILURE);
      }
      
      // report back success, the 266 is just an arbitrary value without 
      // deeper meaning
      finish(266);
      break;
      
    default:
      printf("Impossible state!\n");
      finish(EXIT_FAILURE);
      break;
  }
  
  return;
}