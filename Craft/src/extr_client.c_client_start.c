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
 int /*<<< orphan*/  QUEUE_SIZE ; 
 scalar_t__ calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  client_enabled ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_plain ; 
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ qsize ; 
 char* queue ; 
 int /*<<< orphan*/  recv_thread ; 
 int /*<<< orphan*/  recv_worker ; 
 int running ; 
 scalar_t__ thrd_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ thrd_success ; 

void client_start() {
    if (!client_enabled) {
        return;
    }
    running = 1;
    queue = (char *)calloc(QUEUE_SIZE, sizeof(char));
    qsize = 0;
    mtx_init(&mutex, mtx_plain);
    if (thrd_create(&recv_thread, recv_worker, NULL) != thrd_success) {
        perror("thrd_create");
        exit(1);
    }
}