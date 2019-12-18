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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct hpsb_host {int dummy; } ;
typedef  int /*<<< orphan*/  quadlet_t ;

/* Variables and functions */
#define  CSR_FCP_COMMAND 129 
#define  CSR_FCP_RESPONSE 128 
 int CSR_REGISTER_BASE ; 
 int RCODE_COMPLETE ; 
 int RCODE_TYPE_ERROR ; 
 int /*<<< orphan*/  highlevel_fcp_request (struct hpsb_host*,int,int,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static int write_fcp(struct hpsb_host *host, int nodeid, int dest,
		     quadlet_t *data, u64 addr, size_t length, u16 flags)
{
        int csraddr = addr - CSR_REGISTER_BASE;

        if (length > 512)
                return RCODE_TYPE_ERROR;

        switch (csraddr) {
        case CSR_FCP_COMMAND:
                highlevel_fcp_request(host, nodeid, 0, (u8 *)data, length);
                break;
        case CSR_FCP_RESPONSE:
                highlevel_fcp_request(host, nodeid, 1, (u8 *)data, length);
                break;
        default:
                return RCODE_TYPE_ERROR;
        }

        return RCODE_COMPLETE;
}