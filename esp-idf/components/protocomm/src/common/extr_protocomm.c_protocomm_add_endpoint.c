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
typedef  int /*<<< orphan*/  protocomm_t ;
typedef  int /*<<< orphan*/  protocomm_req_handler_t ;
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_EP ; 
 int /*<<< orphan*/  protocomm_add_endpoint_internal (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

esp_err_t protocomm_add_endpoint(protocomm_t *pc, const char *ep_name,
                                 protocomm_req_handler_t h, void *priv_data)
{
    return protocomm_add_endpoint_internal(pc, ep_name, h, priv_data, REQ_EP);
}