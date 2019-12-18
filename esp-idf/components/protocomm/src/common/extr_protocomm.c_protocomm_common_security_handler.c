#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  pop; int /*<<< orphan*/  sec_inst; TYPE_1__* sec; } ;
typedef  TYPE_2__ protocomm_t ;
struct TYPE_3__ {int (* security_req_handler ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,void*) ;} ;

/* Variables and functions */
 int ESP_OK ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static int protocomm_common_security_handler(uint32_t session_id,
                                             const uint8_t *inbuf, ssize_t inlen,
                                             uint8_t **outbuf, ssize_t *outlen,
                                             void *priv_data)
{
    protocomm_t *pc = (protocomm_t *) priv_data;

    if (pc->sec && pc->sec->security_req_handler) {
        return pc->sec->security_req_handler(pc->sec_inst,
                                             pc->pop, session_id,
                                             inbuf, inlen,
                                             outbuf, outlen,
                                             priv_data);
    }

    return ESP_OK;
}