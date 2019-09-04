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
 scalar_t__ QUEUE_SIZE ; 
 int RECV_SIZE ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ qsize ; 
 scalar_t__ queue ; 
 int recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ running ; 
 int /*<<< orphan*/  sd ; 
 int /*<<< orphan*/  sleep (int /*<<< orphan*/ ) ; 

int recv_worker(void *arg) {
    char *data = malloc(sizeof(char) * RECV_SIZE);
    while (1) {
        int length;
        if ((length = recv(sd, data, RECV_SIZE - 1, 0)) <= 0) {
            if (running) {
                perror("recv");
                exit(1);
            }
            else {
                break;
            }
        }
        data[length] = '\0';
        while (1) {
            int done = 0;
            mtx_lock(&mutex);
            if (qsize + length < QUEUE_SIZE) {
                memcpy(queue + qsize, data, sizeof(char) * (length + 1));
                qsize += length;
                done = 1;
            }
            mtx_unlock(&mutex);
            if (done) {
                break;
            }
            sleep(0);
        }
    }
    free(data);
    return 0;
}