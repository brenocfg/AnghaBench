#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  tag; int /*<<< orphan*/  type; int /*<<< orphan*/  index; int /*<<< orphan*/  grp; } ;
struct TYPE_11__ {TYPE_2__ s; scalar_t__ u64; } ;
typedef  TYPE_4__ cvmx_pow_tag_req_t ;
struct TYPE_10__ {int /*<<< orphan*/  tag; int /*<<< orphan*/  tag_type; int /*<<< orphan*/  index; int /*<<< orphan*/  grp; } ;
struct TYPE_12__ {TYPE_3__ s_sstatus2; int /*<<< orphan*/  u64; } ;
typedef  TYPE_5__ cvmx_pow_tag_load_resp_t ;
struct TYPE_8__ {int is_io; int get_cur; int /*<<< orphan*/  coreid; int /*<<< orphan*/  did; int /*<<< orphan*/  mem_region; } ;
struct TYPE_13__ {scalar_t__ u64; TYPE_1__ sstatus; } ;
typedef  TYPE_6__ cvmx_pow_load_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_IO_SEG ; 
 int /*<<< orphan*/  CVMX_OCT_DID_TAG_TAG1 ; 
 int /*<<< orphan*/  cvmx_get_core_num () ; 
 int /*<<< orphan*/  cvmx_read_csr (scalar_t__) ; 

__attribute__((used)) static inline cvmx_pow_tag_req_t cvmx_pow_get_current_tag(void)
{
	cvmx_pow_load_addr_t load_addr;
	cvmx_pow_tag_load_resp_t load_resp;
	cvmx_pow_tag_req_t result;

	load_addr.u64 = 0;
	load_addr.sstatus.mem_region = CVMX_IO_SEG;
	load_addr.sstatus.is_io = 1;
	load_addr.sstatus.did = CVMX_OCT_DID_TAG_TAG1;
	load_addr.sstatus.coreid = cvmx_get_core_num();
	load_addr.sstatus.get_cur = 1;
	load_resp.u64 = cvmx_read_csr(load_addr.u64);
	result.u64 = 0;
	result.s.grp = load_resp.s_sstatus2.grp;
	result.s.index = load_resp.s_sstatus2.index;
	result.s.type = load_resp.s_sstatus2.tag_type;
	result.s.tag = load_resp.s_sstatus2.tag;
	return result;
}