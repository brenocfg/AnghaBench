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
struct adb_request {int* data; } ;

/* Variables and functions */
 size_t ACR ; 
 size_t B ; 
 size_t SR ; 
 int SR_OUT ; 
 int TIP ; 
 int TREQ ; 
 int /*<<< orphan*/  cuda_state ; 
 struct adb_request* current_req ; 
 int in_8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sent_first_byte ; 
 int /*<<< orphan*/ * via ; 

__attribute__((used)) static void
cuda_start(void)
{
    struct adb_request *req;

    /* assert cuda_state == idle */
    /* get the packet to send */
    req = current_req;
    if (req == 0)
	return;
    if ((in_8(&via[B]) & TREQ) == 0)
	return;			/* a byte is coming in from the CUDA */

    /* set the shift register to shift out and send a byte */
    out_8(&via[ACR], in_8(&via[ACR]) | SR_OUT);
    out_8(&via[SR], req->data[0]);
    out_8(&via[B], in_8(&via[B]) & ~TIP);
    cuda_state = sent_first_byte;
}