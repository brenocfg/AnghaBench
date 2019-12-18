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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int32_t ;
struct TYPE_2__ {int /*<<< orphan*/ * client_handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCHI_FLAGS_BLOCK_UNTIL_OP_COMPLETE ; 
 TYPE_1__ cecservice_client ; 
 int /*<<< orphan*/  vc_cec_log_error (char*) ; 
 int /*<<< orphan*/  vchi2service_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vchi_bulk_queue_receive (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcos_verify (void*) ; 

__attribute__((used)) static int32_t cecservice_wait_for_bulk_receive(void *buffer, uint32_t max_length) {
   if(!vcos_verify(buffer)) {
      vc_cec_log_error("CEC: NULL buffer passed to wait_for_bulk_receive");
      return -1;
   }
   return (int32_t) vchi2service_status(vchi_bulk_queue_receive( cecservice_client.client_handle[0],
                                                                 buffer,
                                                                 max_length,
                                                                 VCHI_FLAGS_BLOCK_UNTIL_OP_COMPLETE,
                                                                 NULL ));
}