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
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void usage(void)
{
    printf("send message to ZMQ recipient, to use with the zmq filters\n");
    printf("usage: zmqsend [OPTIONS]\n");
    printf("\n"
           "Options:\n"
           "-b ADDRESS        set bind address\n"
           "-h                print this help\n"
           "-i INFILE         set INFILE as input file, stdin if omitted\n");
}