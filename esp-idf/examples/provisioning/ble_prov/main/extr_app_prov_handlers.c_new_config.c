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
typedef  int /*<<< orphan*/  wifi_prov_ctx_t ;
typedef  int /*<<< orphan*/  wifi_config_t ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_config (int /*<<< orphan*/ **) ; 

__attribute__((used)) static wifi_config_t *new_config(wifi_prov_ctx_t **ctx)
{
    free(*ctx);
    (*ctx) = (wifi_prov_ctx_t *) calloc(1, sizeof(wifi_prov_ctx_t));
    return get_config(ctx);
}